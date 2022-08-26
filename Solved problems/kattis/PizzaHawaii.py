def main():
    t = int(input())
    for _ in range(t):
        if _: print()
        n = int(input())
        A = dict()
        B = dict()
        for i in range(n):
            name = input() # nombre de la pizza
            tokens = input().strip().split() # ingredientes restaurant 1
            for token in tokens[1:]:
                A[token] = A.get(token, 0) | (1 << i)
            tokens = input().strip().split() # ingredientes restaurant 2
            for token in tokens[1:]:
                B[token] = B.get(token, 0) | (1 << i)
        A = list(A.items())
        A.sort()
        B = list(B.items())
        B.sort()
        for a in A:
            for b in B:
                if a[1] == b[1]:
                    print('(%s, %s)' % (a[0], b[0]))

main()