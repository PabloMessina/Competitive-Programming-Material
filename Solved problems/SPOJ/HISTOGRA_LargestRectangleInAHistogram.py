MAXN = 100000
L = [None] * MAXN
R = [None] * MAXN

if __name__ == '__main__':
    while True:
        N, *H = map(int, input().split())
        if N == 0: break
        
        # Llenamos L
        s = []
        s.append((-1, -1))
        for i in range(0, N):
            while s[-1][1] >= H[i]:
                s.pop()
            L[i] = s[-1][0]
            s.append((i, H[i]))
        
        # Llenamos R
        s = []
        s.append((N, -1))
        for i in range(N-1, -1, -1):
            while s[-1][1] >= H[i]:
                s.pop()
            R[i] = s[-1][0]
            s.append((i, H[i]))
            
        # Encontramos el área más grande
        ans = max((R[i] - L[i] - 1) * H[i] for i in range(N))
        print(ans)