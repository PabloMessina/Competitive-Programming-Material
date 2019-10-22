from truefraction import Fraction

def det(a, b, c, d):
    return a * d - b * c


def polygon_area(points):
    area = Fraction(0)
    for i in range(len(points)):
        p = points[i]
        q = points[(i + 1) % len(points)]
        area += (p[0] - q[0]) * (p[1] + q[1]) / 2
    return area


def betw(l, r, x):
    return min(l, r) <= x <= max(l, r)


def intersect_1d(a, b, c, d):
    if a > b:
        a, b = b, a
    if c > d:
        c, d = d, c
    return max(a, c) <= min(b, d)


class Line:
    def __init__(self, p, q):
        # represents the line ax+by+c=0
        self.p = p
        self.q = q
        self.a = p[1] - q[1]
        self.b = q[0] - p[0]
        self.c = -self.a * p[0] - self.b * p[1]

    def dist(self, point):
        return self.a * point[0] + self.b * point[1] + self.c

    def intersection(self, other):
        if not intersect_1d(self.p[0], self.q[0], other.p[0], other.q[0]) or \
                not intersect_1d(self.p[1], self.q[1], other.p[1], other.q[1]):
            return []
        z = det(self.a, self.b, other.a, other.b)
        if z == 0:
            if self.dist(other.p) != 0 or other.dist(self.p) != 0:
                return []
            a, b, c, d = self.p, self.q, other.p, other.q
            if b < a:
                a, b = b, a
            if d < c:
                c, d = d, c
            left = max(a, c)
            right = min(b, d)
            return [left, right]
        else:
            x = -det(self.c, self.b, other.c, other.b) / z
            y = -det(self.a, self.c, other.a, other.c) / z
            if betw(self.p[0], self.q[0], x) and betw(self.p[1], self.q[1], y) \
                    and betw(other.p[0], other.q[0], x) and betw(other.p[1], other.q[1], y):
                return [[x, y]]
            else:
                return []


def cross(o, a, b):
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])


def left_turn(o, a, b):
    return cross(o, a, b) > 0


def convex_hull(points):
    if len(points) == 0:
        return []
    points.sort()
    lower = []
    for i in range(len(points)):
        while len(lower) >= 2 and not left_turn(lower[-2], lower[-1], points[i]):
            lower.pop()
        lower.append(points[i])
    upper = []
    for i in range(len(points) - 1, -1, -1):
        while len(upper) >= 2 and not left_turn(upper[-2], upper[-1], points[i]):
            upper.pop()
        upper.append(points[i])
    lower.pop()
    upper.pop()
    lower.extend(upper)
    return lower


def is_inside(point, points):
    for i in range(len(points)):
        if cross(points[i], points[(i + 1) % len(points)], point) < 0:
            return False
    return True


if __name__ == "__main__":
    n = int(input().strip())
    points = []
    for _ in range(n):
        points.append(list(map(Fraction, input().split())))
    points = convex_hull(points)
    # print(points)
    m = int(input().strip())
    for _ in range(m):
        ax, ay, bx, by, cx, cy = list(map(Fraction, input().split()))
        triangle = [[ax, ay], [bx, by], [cx, cy]]
        triangle = convex_hull(triangle)
        if len(triangle) < 3:
            print(0)
            continue
        intersection_points = []
        for point in triangle:
            if is_inside(point, points):
                intersection_points.append(point)
        for point in points:
            if is_inside(point, triangle):
                intersection_points.append(point)
        for i in range(len(points)):
            for j in range(3):
                l1 = Line(points[i], points[(i + 1) % len(points)])
                l2 = Line(triangle[j], triangle[(j + 1) % 3])
                intersection_points.extend(l1.intersection(l2))
        # print(intersection_points)
        intersection_points = convex_hull(intersection_points)
        # print(intersection_points)
        area = polygon_area(intersection_points)
        # print(round(area), area)
        print(round(area))

        # import matplotlib.pyplot as plt
        # x = [p[0].as_float() for p in points]
        # y = [p[1].as_float() for p in points]
        # x.append(x[0])
        # y.append(y[0])
        # plt.plot(x, y, "black")
        # x = [p[0].as_float() for p in triangle]
        # y = [p[1].as_float() for p in triangle]
        # x.append(x[0])
        # y.append(y[0])
        # plt.plot(x, y, "red")
        # plt.savefig("failed_test.png")
