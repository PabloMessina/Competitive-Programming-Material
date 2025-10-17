from math import sqrt, atan2
import matplotlib.pyplot as plt

EPS = 1e-12

class P:
    def __init__(self, x: float, y: float):
        self.x = x
        self.y = y

    def __sub__(self, other: 'P') -> 'P':
        return P(self.x - other.x, self.y - other.y)

    def __str__(self) -> str:
        return f"P({self.x}, {self.y})"

    def __repr__(self) -> str:
        return f"P({self.x}, {self.y})"

class Circle:
    def __init__(self, x: float, y: float, r: float):
        self.c = P(x, y)
        self.r = r

class Line:
    def __init__(self, p1: P, p2: P):
        self.p1 = p1
        self.p2 = p2


def intersect_circle_line(c: Circle, l: Line) -> bool:
    # Calculate coefficients a, b, c for the line equation a*x + b*y + c = 0,
    # given the circle center (c.x, c.y), radius c.r, and the line l (l.p1, l.p2).
    # Step 1: Calculate line points relative to the circle center
    p1 = l.p1 - c.c
    p2 = l.p2 - c.c
    # Step 2: Calculate line coefficients
    a = p2.y - p1.y
    b = p1.x - p2.x
    cc = -a * p1.x - b * p1.y
    # Step 3: Calculate the projected point (x0, y0): closest point on the line to the center (now (0, 0))
    x0 = -a * cc / (a * a + b * b)
    y0 = -b * cc / (a * a + b * b)
    # Step 4: Check number of intersection points by comparing squared distance from center to line
    # with the squared radius
    sq = a * a + b * b
    if cc * cc > c.r * c.r * sq + EPS:
        return []
    elif abs(cc * cc - c.r * c.r * sq) < EPS:
        ip1 = P(x0 + c.c.x, y0 + c.c.y)
        return [ip1]
    else:
        d = c.r * c.r - cc * cc / sq
        mult = sqrt(d / sq)
        ip1 = P(x0 + b * mult + c.c.x, y0 - a * mult + c.c.y)
        ip2 = P(x0 - b * mult + c.c.x, y0 + a * mult + c.c.y)
        return [ip1, ip2]

def main():
    # Read input from terminal
    cx = float(input("Enter circle center x: "))
    cy = float(input("Enter circle center y: "))
    r = float(input("Enter circle radius: "))
    x1 = float(input("Enter line point 1 x: "))
    y1 = float(input("Enter line point 1 y: "))
    x2 = float(input("Enter line point 2 x: "))
    y2 = float(input("Enter line point 2 y: "))
    c = Circle(cx, cy, r)
    l = Line(P(x1, y1), P(x2, y2))
    intersections = intersect_circle_line(c, l)
    # Print each intersection point and its angle (atan2(y, x))
    for ip in intersections:
        print(f"Intersection point: {ip}, Angle: {atan2(ip.y, ip.x)}")

    # Plot the circle and the line
    fig, ax = plt.subplots()
    ax.add_patch(plt.Circle((c.c.x, c.c.y), c.r, color='blue', fill=False))
    ax.plot([l.p1.x, l.p2.x], [l.p1.y, l.p2.y], color='red')
    for ip in intersections:
        ax.plot(ip.x, ip.y, 'ro')
        # Plot the coordinates of the intersection point
        ax.text(ip.x, ip.y, f"({ip.x:.3f}, {ip.y:.3f})", color='black', verticalalignment='top', horizontalalignment='center')
    # If there are 2 intersections:
    if len(intersections) == 2:
        # Plot a dashed line between them
        ax.plot([intersections[0].x, intersections[1].x], [intersections[0].y, intersections[1].y], 'k--')
        # Plot a dashed line between the circle center and each intersection point
        ax.plot([c.c.x, intersections[0].x], [c.c.y, intersections[0].y], 'k--')
        ax.plot([c.c.x, intersections[1].x], [c.c.y, intersections[1].y], 'k--')
        # Plot the angle of each intersection point at the midpoint of the line segment between the circle center and the intersection point. Use the greek letter theta for the angle.
        ax.text((c.c.x + intersections[0].x) / 2, (c.c.y + intersections[0].y) / 2, f"θ: {atan2(intersections[0].y, intersections[0].x):.3f}", color='black', verticalalignment='top', horizontalalignment='center')
        ax.text((c.c.x + intersections[1].x) / 2, (c.c.y + intersections[1].y) / 2, f"θ: {atan2(intersections[1].y, intersections[1].x):.3f}", color='black', verticalalignment='top', horizontalalignment='center')
    # Save the plot
    plt.savefig('circle_line_intersection.png')
    plt.close()

if __name__ == "__main__":
    main()