# DOESN'T WORK :(
# GIVES RUNTIME ERROR IN LIVE ARCHIVE :/
# C++ SOLUTION WORKS THOUGH

from sys import stdin, stdout

N = 50
board = [[[0 for i in range(N)] for j in range(N)] for k in range(N)]

dirs = (
    (1, 0, 0),
    (-1, 0, 0),
    (0, 1, 0),
    (0, -1, 0),
    (0, 0, 1),
    (0, 0, -1),
)

def dfs(x, y, z):
    stack = list()
    c = board[x][y][z]
    board[x][y][z] = '*'
    count = 1
    stack.append((x, y, z))
    while len(stack) > 0:
        x, y, z = stack.pop()
        for u in dirs:
            xx, yy, zz = x + u[0], y + u[1], z + u[2]
            if 0 <= xx < M and 0 <= yy < P and 0 <= zz < K and board[xx][yy][zz] == c:
                board[xx][yy][zz] = '*'
                count += 1
                stack.append((xx, yy, zz))
    return count

def main():
    global M, P, K

    case = 1

    while True:
        line = stdin.readline()
        if not line:
            break

        P, K, M = map(int, line.strip().split(' '))

        for x in range(M):            
            for y in range(P):
                line = stdin.readline()
                for z in range(K):
                    board[x][y][z] = line[z]
            stdin.readline()
        
        counts = [[] for _ in range(4)]

        for x in range(M):
            for y in range(P):
                for z in range(K):
                    c = board[x][y][z]
                    if c != '*':
                        counts[ord(c) - ord('a')].append(dfs(x, y, z))

        if case > 1:
            print('')
        print('Case {}:'.format(case))
        for i in range(4):
            c = chr(ord('a')+i)
            if len(counts[i]) > 0:
                counts[i].sort(reverse=True)
                print(c, *counts[i])
            else:
                print(c, '0')
        case += 1

main()