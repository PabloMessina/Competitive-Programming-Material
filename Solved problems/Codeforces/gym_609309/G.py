# def brute_force(a, b, n):
#     count = 0
#     for i in range(n):
#         for j in range(i + 1, n):
#             if a[i] + a[j] > b[i] + b[j]:
#                 count += 1
#     return count

# def brute_force_v2(x, n):
#     count = 0
#     for i in range(n):
#         for j in range(i + 1, n):
#             if x[i] + x[j] > 0:
#                 count += 1
#     return count

def main():
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    x = [a[i] - b[i] for i in range(n)]
    x.sort()
    count = 0
    j = n-1
    for i in range(n-1):
        while j-1 > i and x[i] + x[j-1] > 0:
            j -= 1
        if j <= i:
            j = i + 1
        if x[i] + x[j] > 0:
            count += (n - j)
        
    print(count)
    # brute_force_count = brute_force(a, b, n)
    # print("Brute force count:", brute_force_count)
    # brute_force_count_v2 = brute_force_v2(x, n)
    # print("Brute force v2 count:", brute_force_count_v2)

if __name__ == "__main__":
    main()