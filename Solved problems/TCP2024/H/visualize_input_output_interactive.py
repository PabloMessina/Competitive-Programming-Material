import argparse
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('TkAgg')  # Use TkAgg backend for interactivity

class Point2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Triangle2D:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    def get_centroid(self):
        return Point2D((self.a.x + self.b.x + self.c.x) / 3, (self.a.y + self.b.y + self.c.y) / 3)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--input_file', type=str, required=True)
    parser.add_argument('--output_file', type=str)
    parser.add_argument('--graph_file', type=str)
    parser.add_argument('--figsize', type=int, nargs=2, default=[20, 20])
    parser.add_argument('--crop_coords', type=int, nargs=4)
    args = parser.parse_args()

    if args.crop_coords is not None:
        xmin, ymin, xmax, ymax = args.crop_coords
        assert xmin < xmax
        assert ymin < ymax
    else:
        xmin, ymin, xmax, ymax = -2e9, -2e9, 2e9, 2e9

    # Read input with triangles
    with open(args.input_file, 'r') as f:
        n = int(f.readline())
        triangles = []
        for _ in range(n):
            x1, y1 = map(int, f.readline().split())
            x2, y2 = map(int, f.readline().split())
            x3, y3 = map(int, f.readline().split())
            a = Point2D(x1, y1)
            b = Point2D(x2, y2)
            c = Point2D(x3, y3)
            if all(xmin <= p.x <= xmax and ymin <= p.y <= ymax for p in [a, b, c]):
                triangles.append(Triangle2D(a, b, c))
    
    # Read sequence of points
    if args.output_file is not None:
        with open(args.output_file, 'r') as f:
            xs = []
            ys = []
            while True:
                line = f.readline()
                if not line:
                    break
                x, y = map(int, line.split())
                xs.append(x)
                ys.append(y)

    # Enable interactive mode
    plt.ion()
    
    # Plot triangles
    fig, ax = plt.subplots(figsize=args.figsize)
    for i, t in enumerate(triangles):
        if not all(xmin <= p.x <= xmax and ymin <= p.y <= ymax for p in [t.a, t.b, t.c]):
            continue
        ax.fill([t.a.x, t.b.x, t.c.x], [t.a.y, t.b.y, t.c.y], 'b', alpha=0.1)
        ax.plot([t.a.x, t.b.x, t.c.x, t.a.x], [t.a.y, t.b.y, t.c.y, t.a.y], 'b-')
        centroid = t.get_centroid()
        ax.text(centroid.x, centroid.y, f'{i}', color='red')

    # Plot graph
    if args.graph_file is not None:
        with open(args.graph_file, 'r') as f:
            # Skip first two lines
            f.readline() # start point
            f.readline() # end point
            vertices = set()
            while True:
                line = f.readline()
                if not line:
                    break
                x1, y1, x2, y2 = map(int, line.split())
                if xmin <= x1 <= xmax and ymin <= y1 <= ymax and xmin <= x2 <= xmax and ymin <= y2 <= ymax:
                    ax.plot([x1, x2], [y1, y2], 'm--')
                    vertices.add((x1, y1))
                    vertices.add((x2, y2))
            for v in vertices:
                x, y = v
                ax.plot(x, y, 'ro', markersize=5)
                ax.text(x, y, f'({x}, {y})', color='black', verticalalignment='top', horizontalalignment='center')
    
    # Highlight first and last points
    ps = triangles[0].a
    pe = triangles[-1].c
    ax.plot(ps.x, ps.y, 'ro')
    ax.text(ps.x, ps.y, 'Start', color='red', verticalalignment='bottom')
    ax.plot(pe.x, pe.y, 'ro')
    ax.text(pe.x, pe.y, 'End', color='red', verticalalignment='bottom')

    # Plot sequence of points
    if args.output_file is not None:
        ax.plot(xs, ys, 'g--', linewidth=2)
        ax.plot(xs, ys, 'yo')
        for x, y in zip(xs, ys):
            ax.text(x, y, f'({x}, {y})', color='black', verticalalignment='top', horizontalalignment='center')

    # Set path's length as title
    if args.output_file is not None:
        L = 0
        for i in range(1, len(xs)):
            L += ((xs[i] - xs[i - 1]) ** 2 + (ys[i] - ys[i - 1]) ** 2) ** 0.5
        ax.set_title(f'Path Length: {L:.2f}')

    # Show plot with interactive features
    plt.show(block=True)

if __name__ == '__main__':
    main()
