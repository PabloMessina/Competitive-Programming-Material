from random import randint
    
n, m, p = map(int, input().split())
c = [input() for _ in range(n)]
max_size = 0
ans = ['0'] * m
for _ in range(10):
    x = randint(0, n-1)
    idxs = []
    for i in range(m):
        if c[x][i] == '1':
            idxs.append(i)
    p = len(idxs)
    f = [0] * (1 << p)
    for i in range(n):
        mask = 0
        for j in range(p):
            if c[i][idxs[j]] == '1':
                mask |= (1 << j)
        f[mask] += 1
    for i in range(p):
        for s in range(1 << p):
            if (s & (1 << i)) == 0:
                f[s] += f[s | (1 << i)]
    for s in range(1, 1 << p):
        if f[s] * 2 < n:
            continue
        n_ones = sum(1 for i in range(p) if (s & (1 << i)) > 0)
        if n_ones <= max_size:
            continue
        max_size = n_ones
        for i in range(m): ans[i] = '0'
        for i in range(p):
            if s & (1 << i): ans[idxs[i]] = '1'

print (''.join(ans))