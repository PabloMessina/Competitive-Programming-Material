import heapq
MOD =  1000000007
def mul(a, b):
    return (a*b)%MOD
def add(a, b):
    return (a+b)%MOD

def main():
    T = int(input())
    for _ in range(T):
        a, b, c, n = map(int, input().split())
        lower = []
        upper = []
        sum = 1
        heapq.heappush(lower, -1)
        for i in range(2, n+1):
            median = -lower[0]
            x = add(add(mul(a,median),mul(b,i)),c)
            sum += x
            if x > median:
                heapq.heappush(upper, x)
                if (len(upper) > len(lower)):
                    heapq.heappush(lower, -heapq.heappop(upper))
            else:
                heapq.heappush(lower, -x)
                if (len(lower) > len(upper) + 1):
                    heapq.heappush(upper, -heapq.heappop(lower))
        print(sum)

main()