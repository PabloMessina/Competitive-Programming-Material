def main():
    t = int(input())
    for _ in range(t):
        n = int(input())
        vals = list(map(int, input().split()))
        if sum(vals) % 2 == 0:
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    main()