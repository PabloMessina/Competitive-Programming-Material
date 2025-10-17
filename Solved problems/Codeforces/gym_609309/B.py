def main():
    t = int(input())
    for _ in range(t):
        b, c, h = map(int, input().split())
        x = c + h
        if b > x:
            print(2 * x + 1)
        else:
            print(2 * (b-1) + 1)

if __name__ == "__main__":
    main()