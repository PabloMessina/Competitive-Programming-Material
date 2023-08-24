def main():
    n = int(input())
    tuples = []
    seen_pairs = set()
    for i in range(n):
        l, r = map(int, input().split())
        tuples.append((2 * l - 1, 2 * r + 1, i))
        pair = (tuples[-1][0], tuples[-1][1])
        if pair in seen_pairs:
            print(i + 1)
            return
        seen_pairs.add(pair)
    tuples.sort(key=lambda x: (x[0], -x[1]))
    l = -2
    r = -2
    prev_i = -1
    for t in tuples:
        assert l <= r
        if t[0] <= l and r <= t[1]:
            print(prev_i + 1)
            return
        if t[1] <= r:
            print(t[2] + 1)
            return
        l = max(t[0], r)
        r = t[1]
        prev_i = t[2]
    print(-1)
main()