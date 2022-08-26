import random
n = random.randint(2, 5)
S = [random.randint(0, 1e9) for _ in range(n-1)]
D = [random.randint(0, 1e9) for _ in range(n)]
F = [random.randint(0, 1e9) for _ in range(n+1)]
print(n)
print(' '.join(map(str, S)))
print(' '.join(map(str, D)))
print(' '.join(map(str, F)))