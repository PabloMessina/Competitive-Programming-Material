from random import randint

for _ in range(100000):
    cx = randint(-1000, 1000)
    cy = randint(-1000, 1000)
    r = randint(1, 1000)
    x1 = randint(-1000, 1000)
    while True:
        x2 = randint(-1000, 1000)
        if x1 != x2:
            break
    y1 = randint(-1000, 1000)
    while True:
        y2 = randint(-1000, 1000)
        if y1 != y2:
            break
    print('%d %d %d\n%d %d %d %d' % (cx,cy,r,x1,y1,x2,y2))