import random


L1 = 1000000
L2 = 3000000

n = 60
print(n)
for _ in range(n):
    print(" ".join(map(str, (random.randint(-L1, L1) for _ in range(2)))))
m = 1000
print(m)
for _ in range(m):
    print(" ".join(map(str, (random.randint(-L2, L2) for _ in range(6)))))