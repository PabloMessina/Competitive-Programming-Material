import sys
from random import randint

n_tests, N, R, K = map(int, sys.argv[1:])
print('5 2 3')
print('2 4')
print('1 2 1')
print('1 1 1')
print('1234 4 4')
print('23 25 1000 67')
print('20 4 26 222')
print('18 28 1232 222')
print('2 4 6 222')
print('2 2 2 2')
print('2 2 1')
print('1 2')
print('1')
print('1')
for _ in range(n_tests):
    print(N, R, K)
    print(*[randint(1,N) for _ in range(R)])
    for r in range(R):
        print(*[randint(1,N-1) for _ in range(K)])