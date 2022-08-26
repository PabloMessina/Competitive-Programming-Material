# TODO: finish this
import math

def sieve(n):
    isprime = [True] * n
    limit = math.floor(math.sqrt(n))
    for i in range(2, limit+1):
        if isprime[i]:
            for j in range(i*i, n+1, i):
                isprime[j] = False
    primes = []
    for i in range(2, n):
        if isprime[i]:
            primes.append(i)
    return primes

def get_prime_factorization(x, primes):
    fact = dict()
    for p in primes:
        if p * p > x: break
        while (x % p == 0):
            fact[p] = fact.get(p, 0) + 1
            x /= p
    if x > 1:
        fact[x] = fact.get(x, 0) + 1

def main():
    a, b = map(int, input().split())
    primes = sieve()
    fact_a = get_prime_factorization(a)
    fact_b = get_prime_factorization(b)

    pass

main()