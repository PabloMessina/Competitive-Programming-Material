import random
P = 3
L = 3
R = 4
V = 10
used = set()
print(P, L)
while len(used) < P + L:
    x = random.randint(-R, R)
    y = random.randint(-R, R)
    p = (x,y)
    if p in used: continue
    used.add(p)
    print(x, y, random.randint(1, V))
print(0, 0)