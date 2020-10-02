def deltaAccH(i, j):
    return (accH[j] - accH[i-1]) if i > 0 else accH[j]
def deltaAccKH(i, j):
    return (accKH[j] - accKH[i-1]) if i > 0 else accKH[j]
def cost(i, j):
    if i < 0: return j * accH[j] - accKH[j]
    if j >= N: return deltaAccKH(i, N-1) - i * deltaAccH(i, N-1)
    ml = (i+j)>>1
    mr = ml+1
    lcost = deltaAccKH(i, ml) - i * deltaAccH(i, ml)
    rcost = j * deltaAccH(mr, j) - deltaAccKH(mr, j)
    return lcost + rcost
def fill(k, i1, i2, j1, j2):
    if i1 > i2: return
    im = (i1+i2) >> 1
    jmin = max(j1, k-1)
    jmax = min(j2, im)
    minv = 9999999999
    bestj = -1
    for j in range(jmin, jmax+1):
        v = cost(j,im+1) + (dp[k-1][j-1] if j > 0 else 0)
        if v < minv: minv, bestj = v, j
    dp[k][im] = minv
    fill(k,i1,im-1,j1,bestj)
    fill(k,im+1,i2,bestj,j2)
def main():
    global N, B, C, H, accH, accKH, dp
    N, B, C = map(int, input().split())
    H = list(map(int, input().split()))
    accH = [0] * N
    accKH = [0] * N
    accH[0] = H[0]
    for k in range(1,N):
        accH[k] = accH[k-1] + H[k]
        accKH[k] = accKH[k-1] + H[k] * k
    dp = [[None] * N for _ in range(N+1)]
    for i in range(N-1):
        dp[0][i] = cost(-1, i+1)
    for k in range(1, N+1): fill(k, k-1, N-1, 0, N-1)
    for k in range(1, N+1):
        if k > 1: print(" ", end="")
        total_cost = dp[k][N-1] * C + k * B
        print(total_cost, end="")
    print()

main()