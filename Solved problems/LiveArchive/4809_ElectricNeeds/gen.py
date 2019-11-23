import random
N = 6
M = 6
P = 2
Q = N*M - P
sample = random.sample(range(N*M), P)
print(N, M, P)
for i in range(P):
    r = sample[i] // M
    c = sample[i] % M
    print(r+1, c+1)
print(Q)
print(' '.join(map(str, range(1, Q+1))))
print('0 0 0')