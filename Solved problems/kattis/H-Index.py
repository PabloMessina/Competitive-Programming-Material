def main():
    n = int(input())
    h = [int(input()) for _ in range(n)]
    h.sort(reverse=True)
    ans = 0
    for i in range(n):
        if i+1 > h[i]:
            break
        ans = i+1
    print(ans)
main()