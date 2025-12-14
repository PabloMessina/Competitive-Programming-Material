def main():
    n = int(input())
    a = list(map(int, input().split()))
    for i in range(n):
        if a[i] >= 0:
            a[i] = -1 - a[i]
    if len(a) % 2 == 1:
        i, _ = min(enumerate(a), key=lambda x: x[1])
        a[i] = -1 - a[i]
    print(' '.join(map(str, a)))

if __name__ == "__main__":
    main()