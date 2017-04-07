from sys import stdin
from collections import deque

dirs = ((-1, 0), (1, 0), (0, -1), (0, 1))

def fill(r, c):
    board[r][c] = 'B'
    q = deque()
    q.append((r, c))
    while q:
        r, c = q.popleft()
        for u in dirs:
            rr, cc = r + u[0], c + u[1]
            if 0 <= rr < n and 0 <= cc < m and board[rr][cc] == '.':
                board[rr][cc] = 'W' if board[r][c] == 'B' else 'B'
                q.append((rr, cc))

def main():
    global n, m, board

    line = stdin.readline()
    n, m = map(int, line.strip().split(' '))

    board = [[None for _ in range(m)] for _ in range(n)]
    for r in range(n):
        line = stdin.readline()
        for c in range(m):
            board[r][c] = line[c]

    for r in range(n):
        for c in range(m):
            if board[r][c] == '.':
                fill(r, c)
            print(board[r][c], end='')
        print('')

main()