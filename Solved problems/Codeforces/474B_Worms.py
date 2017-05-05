def main():
    n = int(input())
    a = list(map(int, input().split()))
    m = int(input())
    q = list(map(int, input().split()))
    acc_a = [0] * n
    acc = 0
    for i, x in enumerate(a):
        acc = acc_a[i] = x + acc
    for x in q:
        low, high = 0, n-1
        while low < high:
            mid = (low+high)>>1
            if x <= acc_a[mid]:
                high = mid
            else:
                low = mid + 1
        print(low+1)
        
main()