import argparse
import math
from random import randint

class Point2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    def __sub__(self, other):
        return Point2D(self.x - other.x, self.y - other.y)
    def __add__(self, other):
        return Point2D(self.x + other.x, self.y + other.y)
    def __xor__(self, other):
        return self.x * other.y - self.y * other.x # cross product
    def __mul__(self, other):
        if isinstance(other, Point2D):
            return self.x * other.x + self.y * other.y # dot product
        assert isinstance(other, (int, float))
        return Point2D(self.x * other, self.y * other) # scalar multiplication
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    def __ne__(self, other):
        return not self == other
    def norm2(self):
        return self.x * self.x + self.y * self.y
    def norm(self):
        return self.norm2() ** 0.5
    def __repr__(self):
        return f'Point2D({self.x}, {self.y})'

class Triangle2D:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    def area(self):
        return abs((self.b.x - self.a.x) * (self.c.y - self.a.y) - (self.c.x - self.a.x) * (self.b.y - self.a.y)) / 2
    def check_valid(self):
        ab_len = (self.b - self.a).norm()
        bc_len = (self.c - self.b).norm()
        ca_len = (self.a - self.c).norm()
        return ab_len + bc_len > ca_len and bc_len + ca_len > ab_len and ca_len + ab_len > bc_len and self.area() > 0
    def get_centroid(self):
        return Point2D((self.a.x + self.b.x + self.c.x) / 3, (self.a.y + self.b.y + self.c.y) / 3)
    
def turn(a, b, c):
    return (b-a)^(c-a)

def turn_sign(a, b, c):
    t = turn(a, b, c)
    return 1 if t > 0 else -1 if t < 0 else 0

def on_line(a, b, p):
    return turn(a, b, p) == 0
    
def in_disk(a, b, p, strict=False):
    if strict:
        return (a-p)*(b-p) < 0
    return (a-p)*(b-p) <= 0

def on_segment(a, b, p, strict=False):
    return on_line(a, b, p) and in_disk(a, b, p, strict)

def point_in_triangle(p, t):
    a, b, c = t.a, t.b, t.c
    turn_abp = turn(a, b, p)
    turn_bcp = turn(b, c, p)
    turn_cap = turn(c, a, p)
    return (turn_abp >= 0 and turn_bcp >= 0 and turn_cap >= 0) or\
              (turn_abp <= 0 and turn_bcp <= 0 and turn_cap <= 0)

def do_segments_intersect(p1, q1, p2, q2, strict=False):
    t11 = turn_sign(p1, q1, p2)
    t12 = turn_sign(p1, q1, q2)
    t21 = turn_sign(p2, q2, p1)
    t22 = turn_sign(p2, q2, q1)
    if strict:
        if abs(t11 - 12) == 2 and abs(t21 - t22) == 2:
            return True
        if t11 == t12 and t11 == 0:
            return on_segment(p1, q1, p2, strict) or on_segment(p2, q2, p1, strict)
    if t11 != t12 and t21 != t22:
        return True
    if t11 == t12 and t11 == 0:
        return on_segment(p1, q1, p2) or on_segment(p2, q2, p1)
    return False

def do_triangles_intersect(t1, t2):
    if point_in_triangle(t1.a, t2) or point_in_triangle(t1.b, t2) or point_in_triangle(t1.c, t2):
        return True
    if point_in_triangle(t2.a, t1) or point_in_triangle(t2.b, t1) or point_in_triangle(t2.c, t1):
        return True
    if do_segments_intersect(t1.a, t1.b, t2.a, t2.b) or\
         do_segments_intersect(t1.a, t1.b, t2.b, t2.c) or\
         do_segments_intersect(t1.a, t1.b, t2.c, t2.a) or\
         do_segments_intersect(t1.b, t1.c, t2.a, t2.b) or\
         do_segments_intersect(t1.b, t1.c, t2.b, t2.c) or\
         do_segments_intersect(t1.b, t1.c, t2.c, t2.a) or\
         do_segments_intersect(t1.c, t1.a, t2.a, t2.b) or\
         do_segments_intersect(t1.c, t1.a, t2.b, t2.c) or\
         do_segments_intersect(t1.c, t1.a, t2.c, t2.a):
          return True
    return False

def do_triangles_only_share_one_vertex(t1, t2):
    t1_nonshared_vertexes = []
    t2_nonshared_vertexes = []
    if t1.a != t2.a and t1.a != t2.b and t1.a != t2.c:
        t1_nonshared_vertexes.append(t1.a)
    if t1.b != t2.a and t1.b != t2.b and t1.b != t2.c:
        t1_nonshared_vertexes.append(t1.b)
    if t1.c != t2.a and t1.c != t2.b and t1.c != t2.c:
        t1_nonshared_vertexes.append(t1.c)
    if t2.a != t1.a and t2.a != t1.b and t2.a != t1.c:
        t2_nonshared_vertexes.append(t2.a)
    if t2.b != t1.a and t2.b != t1.b and t2.b != t1.c:
        t2_nonshared_vertexes.append(t2.b)
    if t2.c != t1.a and t2.c != t1.b and t2.c != t1.c:
        t2_nonshared_vertexes.append(t2.c)
    if len(t1_nonshared_vertexes) == 2 and len(t2_nonshared_vertexes) == 2:
        # This means that the triangles share only one vertex.
        # We need to check now if none of non-shared vertexes are inside the other triangle
        for p in t1_nonshared_vertexes:
            if point_in_triangle(p, t2):
                return False
        for p in t2_nonshared_vertexes:
            if point_in_triangle(p, t1):
                return False
        # We need to check now if edges connecting the non-shared vertexes intersect
        # edges of the other triangle
        if do_segments_intersect(t1_nonshared_vertexes[0], t1_nonshared_vertexes[1], t2.a, t2.b) or\
            do_segments_intersect(t1_nonshared_vertexes[0], t1_nonshared_vertexes[1], t2.b, t2.c) or\
            do_segments_intersect(t1_nonshared_vertexes[0], t1_nonshared_vertexes[1], t2.c, t2.a):
            return False
        if do_segments_intersect(t2_nonshared_vertexes[0], t2_nonshared_vertexes[1], t1.a, t1.b) or\
            do_segments_intersect(t2_nonshared_vertexes[0], t2_nonshared_vertexes[1], t1.b, t1.c) or\
            do_segments_intersect(t2_nonshared_vertexes[0], t2_nonshared_vertexes[1], t1.c, t1.a):
            return False
        return True
    return False

def gen_first_triangle(xmin, xmax, ymin, ymax, max_width, max_height, min_area):
    # fit a rectangle in the center of the bounding box
    x1 = (xmin + xmax - max_width) // 2
    y1 = (ymin + ymax - max_height) // 2
    x2 = x1 + max_width
    y2 = y1 + max_height
    while True:
        # choose a random triangle inside the rectangle
        a = Point2D(randint(x1, x2), randint(y1, y2))
        b = Point2D(randint(x1, x2), randint(y1, y2))
        c = Point2D(randint(x1, x2), randint(y1, y2))
        t = Triangle2D(a, b, c)
        if t.check_valid() and t.area() >= min_area:
            return t
        
def get_point_line_unit_normal(p, a, b):
    d = b - a
    t = (d * (p - a)) / d.norm2()
    v = a + d * t - p
    return v * (1 / v.norm())

def gen_next_triangle(previous_triangles, max_width, max_height, min_area, max_attempts=200):
    assert len(previous_triangles) > 0
    t = previous_triangles[-1] # last triangle
    for _ in range(max_attempts):
        # Choose a random edge of the triangle
        edge = randint(0, 2)
        if edge == 0:
            a, b, c = t.a, t.b, t.c
        elif edge == 1:
            a, b, c = t.b, t.c, t.a
        else:
            a, b, c = t.c, t.a, t.b
        # Define a rectangle with a corner in the middle of the edge and away from the triangle
        x1 = (a.x + b.x) // 2
        y1 = (a.y + b.y) // 2
        normal = get_point_line_unit_normal(c, a, b)
        center = Point2D(x1, y1) + normal * math.sqrt(max_width**2 + max_height**2) * 0.5
        x1 = int(center.x - max_width * 0.5)
        y1 = int(center.y - max_height * 0.5)
        x2 = x1 + max_width
        y2 = y1 + max_height
        # Choose a random point inside the rectangle but outside the triangle respecting the constraints
        x = randint(x1, x2)
        y = randint(y1, y2)
        p = Point2D(x, y)
        if point_in_triangle(p, t) or\
            do_segments_intersect(a, p, b, c) or\
            do_segments_intersect(b, p, a, c):
            continue # try again
        next_triangle = Triangle2D(a, b, p)
        if point_in_triangle(c, next_triangle):
            continue # try again
        if not next_triangle.check_valid():
            continue # try again
        if next_triangle.area() < min_area:
            continue # try again
        # Check if the new triangle intersects with any of the previous triangles
        valid = True
        count = 0
        for i in range(len(previous_triangles) - 2, -1, -1):
            tt = previous_triangles[i]
            if do_triangles_intersect(tt, next_triangle):
                if do_triangles_only_share_one_vertex(tt, next_triangle) and (len(previous_triangles)-i-1) == count+1:
                    count += 1
                    continue
                valid = False
                break
        if valid:
            return next_triangle
    raise Exception(f'Could not generate a valid triangle after {max_attempts} attempts')

def save_triangles_to_image(triangles, filename, figsize):
    import matplotlib.pyplot as plt
    fig, ax = plt.subplots(figsize=figsize)
    for i, t in enumerate(triangles):
        plt.plot([t.a.x, t.b.x, t.c.x, t.a.x], [t.a.y, t.b.y, t.c.y, t.a.y], 'b-')
        c = t.get_centroid()
        plt.text(c.x, c.y, str(i), color='red', fontsize=12, ha='center', va='center')
    # Highlight first point (S, green) and last point (T, purple)
    plt.plot(triangles[0].a.x, triangles[0].a.y, 'go', markersize=10)
    plt.text(triangles[0].a.x, triangles[0].a.y, 'S', color='green', fontsize=20, ha='center', va='center')
    plt.plot(triangles[-1].c.x, triangles[-1].c.y, 'mo', markersize=10)
    plt.text(triangles[-1].c.x, triangles[-1].c.y, 'T', color='purple', fontsize=20, ha='center', va='center')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid(True)
    plt.savefig(filename)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--n', type=int, default=2)
    parser.add_argument('--xmin', type=int, default=0)
    parser.add_argument('--xmax', type=int, default=100)
    parser.add_argument('--ymin', type=int, default=0)
    parser.add_argument('--ymax', type=int, default=100)
    parser.add_argument('--max_width', type=int, default=20)
    parser.add_argument('--max_height', type=int, default=20)
    parser.add_argument('--min_area', type=float, default=1)
    parser.add_argument('--save_figure', action='store_true')
    parser.add_argument('--save_txt', action='store_true')
    parser.add_argument('--figsize', type=float, nargs=2, default=[6, 6])
    args = parser.parse_args()
    n = args.n
    xmin = args.xmin
    xmax = args.xmax
    ymin = args.ymin
    ymax = args.ymax
    max_width = args.max_width
    max_height = args.max_height
    min_area = args.min_area
    assert 2 <= n <= 10**5
    assert -10**9 <= xmin <= xmax <= 10**9
    assert -10**9 <= ymin <= ymax <= 10**9
    assert 1 <= max_width <= 10**9
    assert 1 <= max_height <= 10**9
    print(n)
    triangles = []
    triangles.append(gen_first_triangle(xmin, xmax, ymin, ymax, max_width, max_height, min_area)) # first triangle
    max_patience = 5
    patience = max_patience
    min_n_to_pop = 5
    n_to_pop = min_n_to_pop
    last_len = 1
    progress_margin = 50

    while len(triangles) < n:
        try:
            triangles.append(gen_next_triangle(triangles, max_width, max_height, min_area))
        except Exception as e:
            # save_triangles_to_image(triangles, 'triangles(debug).png', args.figsize)
            # raise e
            # Backgtrack and try again (remove last 4 triangles)

            if len(triangles) > last_len + progress_margin:
                # it seems we made more progress than before, so let's be more patient now
                if n_to_pop > min_n_to_pop:
                    n_to_pop //= 2
                    patience = max_patience

            last_len = len(triangles)

            print(f'Pop {n_to_pop} triangles')
            for _ in range(n_to_pop):
                if len(triangles) == 1:
                    break
                triangles.pop()
            
            patience -= 1
            if patience == 0:
                n_to_pop *= 2 # increase n_to_pop exponentially to avoid infinite loop
                patience = max_patience
            
            if len(triangles) == 1:
                n_to_pop = min_n_to_pop # reset n_to_pop

    for t in triangles:
        print(t.a.x, t.a.y)
        print(t.b.x, t.b.y)
        print(t.c.x, t.c.y)
    if args.save_figure:
        save_triangles_to_image(triangles, 'triangles.png', args.figsize)
    if args.save_txt:
        # save the triangles to a file
        with open('triangles.txt', 'w') as f:
            f.write(f'{n}\n')
            for t in triangles:
                f.write(f'{t.a.x} {t.a.y}\n')
                f.write(f'{t.b.x} {t.b.y}\n')
                f.write(f'{t.c.x} {t.c.y}\n')

def debug_case():
    # 221 -35
    # 193 -17
    # 192 -36

    # 201 -16
    # 221 -35
    # 175 -39
    t1 = Triangle2D(
        Point2D(221, -35),
        Point2D(193, -17),
        Point2D(192, -36)
    )
    t2 = Triangle2D(
        Point2D(201, -16),
        Point2D(221, -35),
        Point2D(175, -39)
    )
    print(f'do_triangles_intersect(t1, t2) = {do_triangles_intersect(t1, t2)}')
    print(f'do_triangles_only_share_one_vertex(t1, t2) = {do_triangles_only_share_one_vertex(t1, t2)}')
    # generate plot and save it for debugging
    import matplotlib.pyplot as plt
    fig, ax = plt.subplots(figsize=(6, 6))
    plt.plot([t1.a.x, t1.b.x], [t1.a.y, t1.b.y], 'r-')
    plt.plot([t1.b.x, t1.c.x], [t1.b.y, t1.c.y], 'r-')
    plt.plot([t1.c.x, t1.a.x], [t1.c.y, t1.a.y], 'r-')
    plt.plot([t2.a.x, t2.b.x], [t2.a.y, t2.b.y], 'b-')
    plt.plot([t2.b.x, t2.c.x], [t2.b.y, t2.c.y], 'b-')
    plt.plot([t2.c.x, t2.a.x], [t2.c.y, t2.a.y], 'b-')
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid(True)
    plt.savefig('triangles(debug).png')

if __name__ == '__main__':
    main()
    # debug_case()