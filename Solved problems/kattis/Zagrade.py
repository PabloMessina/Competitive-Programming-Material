def main():
    # parte 1
    line = input().strip()
    stack = []
    brackets = []
    for i in range(len(line)):
        if line[i] == '(':
            stack.append(i)
        elif line[i] == ')':
            brackets.append((stack.pop(), i))
    n = len(brackets)
    # parte 2
    expressions = set()
    for mask in range(1, 1 << n): # bitwise operator x << n == x * (2 ^ n)
        skip = [False] * len(line)
        for j in range(n):
            if (1 << j) & mask > 0:
                skip[brackets[j][0]] = True
                skip[brackets[j][1]] = True
        exp = ''
        for j, c in enumerate(line):
            if skip[j]: continue
            exp += c
        expressions.add(exp)
    expressions = sorted(list(expressions))
    for exp in expressions:
        print(exp)

main()