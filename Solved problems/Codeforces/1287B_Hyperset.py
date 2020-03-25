def main():
    n, k = map(int, input().split())
    cards = []
    for i in range(n):
        cards.append(input().strip())
    cards_set = set(cards)
    ways = 0
    for i in range(n):
        for j in range(i+1, n):
            s = ''
            for z in range(k):
                if cards[i][z] == cards[j][z]:
                    s += cards[i][z]
                else:
                    for c in "SET":
                        if c != cards[i][z] and c != cards[j][z]:
                            s += c
                            break
            if s in cards_set:
                ways += 1
    ways //= 3
    print(ways)

main()