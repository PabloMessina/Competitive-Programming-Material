import random
m = 20
n = 20
minx = 1
maxx = 10
miny = 1
maxy = 10
print(m, n)
for _ in range(m+n):
    x = random.randint(minx, maxx)
    y = random.randint(miny, maxy)
    print(x, y)


