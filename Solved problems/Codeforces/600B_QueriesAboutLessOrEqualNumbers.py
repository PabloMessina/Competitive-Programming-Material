def main():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = [(i,x) for i,x in enumerate(map(int, input().split()))]
    a.sort()
    b.sort(key=lambda p:p[1])
    j = -1
    output = [None] * m
    for i,x in b:
        while (j+1 < n and a[j+1] <= x):
            j += 1
        output[i] = j+1
    for i in range(m):
        if i > 0:
            print(' ', end='')
        print(output[i], end='')
    print('')

main()