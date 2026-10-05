# N. Number of Strings

- Problem: [Codeforces Gym 106682 N](https://codeforces.com/gym/106682/problem/N) (2026 Argentinian Programming Tournament, TAP)
- Solution: [`gym_106682N_NumberOfStrings.cpp`](../../Codeforces/gym_106682N_NumberOfStrings.cpp)

**Problem.** Count the strings of length $N$ over an alphabet of $A$ letters that contain exactly
$K$ palindromic substrings of length 3 (each occurrence counted separately), modulo $998244353$.
Constraints: $N, K \le 10^6$, $2 \le A \le 26$.

**Tags.** combinatorics, binomial coefficients, modular arithmetic, Fermat's little theorem.

---

## Summary: the key points

1. **A length-3 palindrome only depends on its two ends.**
   - $s[i..i+2]$ is a palindrome $\iff$ $s[i] = s[i+2]$. The middle letter doesn't matter.
   - So each of the $N - 2$ windows is a "same / different" constraint on the pair $(i, i+2)$.

2. **The string splits into two independent chains.**
   - Draw an edge $i - (i+2)$ per window. Positions split into the even chain
     $s_0 - s_2 - s_4 - \cdots$ and the odd chain $s_1 - s_3 - s_5 - \cdots$.
   - Each edge is tagged "same" (palindrome) or "different" (not a palindrome).

3. **For a fixed tagging, the count only depends on how many edges are "same".**
   - Color a chain left to right: $A$ choices for the first node, then 1 choice per "same" edge
     and $A - 1$ per "different" edge, whatever the previous color was.
   - So a chain with $m$ edges, $j$ of them "same", has $A \cdot (A-1)^{m-j}$ colorings.

4. **Count all taggings of a chain at once with a binomial.**
   - There are $\binom{m}{j}$ ways to choose which $j$ edges are "same":
     $\mathrm{chain}(m, j) = \binom{m}{j} \cdot A \cdot (A-1)^{m-j}$.

5. **Combine the two chains by splitting $K$.**
   - With $m_1$ and $m_2$ edges: answer $= \sum_k \mathrm{chain}(m_1, k) \cdot \mathrm{chain}(m_2, K - k)$.

6. **Compute it with factorials, inverse factorials and care with edge cases.**
   - One modular inverse (Fermat), then all inverse factorials backwards. $O(N)$ overall.
   - Edge cases: $N = 1$, and $K > N - 2$.

---

## In depth

### 1. A length-3 palindrome only depends on its two ends

A string $xyz$ reads the same backwards iff $x = z$; the middle letter $y$ is unconstrained.
So "exactly $K$ palindromic substrings of length 3" means: among the $N - 2$ pairs
$(s_i, s_{i+2})$ for $i = 0, \ldots, N-3$, exactly $K$ are equal.

### 2. The string splits into two independent chains

Draw a graph on the positions with an edge between $i$ and $i + 2$ for every window. Every edge
joins two positions with the same parity, so the graph is two separate paths:

- even chain: $s_0 - s_2 - s_4 - \cdots$, with $\lceil N/2 \rceil$ nodes;
- odd chain: $s_1 - s_3 - s_5 - \cdots$, with $\lfloor N/2 \rfloor$ nodes.

Each edge is a window. Tag it "same" if its two letters are equal (a palindrome), "different"
otherwise. The two chains share no positions, so they can be colored independently.

*Example* ($N = 5$): even chain $\{0, 2, 4\}$ has $m_1 = 2$ edges, odd chain $\{1, 3\}$ has
$m_2 = 1$ edge. Total $m_1 + m_2 = 3 = N - 2$ windows.

### 3. For a fixed tagging, the count only depends on how many edges are "same"

Fix the tags on a chain with $m$ edges, $j$ of them "same", and color it from left to right:

- the first node: $A$ choices;
- across a "same" edge: the next node must copy the previous color, 1 choice;
- across a "different" edge: any color except the previous one, $A - 1$ choices, **no matter
  which color** the previous node had.

Each node only depends on its predecessor, and the number of choices never depends on the actual
colors, so the count is a plain product:

$$A \cdot 1^{j} \cdot (A-1)^{m-j} = A \cdot (A-1)^{m-j}.$$

It depends on **how many** edges are "same", not **which** ones. This is the observation that makes
the "too many tagging combinations" problem go away: no DP over colors is needed.

### 4. Count all taggings of a chain at once with a binomial

Every choice of which $j$ edges are "same" gives the same count, and there are $\binom{m}{j}$ such
choices:

$$\mathrm{chain}(m, j) = \binom{m}{j} \cdot A \cdot (A-1)^{m-j}.$$

### 5. Combine the two chains by splitting $K$

If the even chain has $k$ palindromes, the odd chain must have $K - k$. The chains are independent,
so the counts multiply:

$$\text{answer} = \sum_{k} \mathrm{chain}(m_1, k) \cdot \mathrm{chain}(m_2, K - k),$$

with $m_1 = \lceil N/2 \rceil - 1$ and $m_2 = \lfloor N/2 \rfloor - 1$. A chain can't have more
palindromes than edges, so $k$ ranges over $\max(0, K - m_2) \le k \le \min(K, m_1)$.

*Example* ($N = 5, K = 2, A = 3$, so $m_1 = 2$, $m_2 = 1$):

| $k$ | $\mathrm{chain}(2, k)$ | $\mathrm{chain}(1, 2 - k)$ | product |
|---|---|---|---|
| 1 | $\binom{2}{1} \cdot 3 \cdot 2^1 = 12$ | $\binom{1}{1} \cdot 3 \cdot 2^0 = 3$ | 36 |
| 2 | $\binom{2}{2} \cdot 3 \cdot 2^0 = 3$ | $\binom{1}{0} \cdot 3 \cdot 2^1 = 6$ | 18 |

Total $36 + 18 = 54$, matching the second sample.

*Bonus.* The powers of $A$ and $A - 1$ are the same in every term ($A^2 (A-1)^{N-2-K}$); only the
binomials change. By Vandermonde's identity, $\sum_k \binom{m_1}{k}\binom{m_2}{K-k} = \binom{N-2}{K}$,
so the answer is simply $\binom{N-2}{K} \cdot A^2 \cdot (A-1)^{N-2-K}$ for $N \ge 2$. The loop is
fast enough anyway, and closer to the reasoning.

### 6. Compute it with factorials, inverse factorials and care with edge cases

**Binomials mod a prime.** $\binom{n}{k} = n! \cdot (k!)^{-1} \cdot ((n-k)!)^{-1} \pmod p$, so we
precompute `fact[i]` and `inv_fact[i]` up to $N$.

**Fermat's little theorem.** If $p$ is prime and $a$ is not a multiple of $p$, then
$a^{p-1} \equiv 1 \pmod p$, so $a^{p-2} \equiv a^{-1} \pmod p$. The inverse is one fast power,
$O(\log p)$. It applies to $N!$ because $N \le 10^6 < p$, so $N!$ has no factor $p$.

**Only one inverse is needed.** Compute `inv_fact[N]` with Fermat, then go backwards using
$(i-1)! = i!/i$:

$$\frac{1}{(i-1)!} = i \cdot \frac{1}{i!} \quad\Longrightarrow\quad \texttt{inv\_fact[i-1]} = \texttt{inv\_fact[i]} \cdot i.$$

**Overflow.** Every value is below $p < 2^{30}$, so a product of two fits in a `long long`. Reduce
after **each** multiplication: `fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD` (`*` and `%`
have the same precedence and associate left to right).

**Edge cases.**

- $N = 1$: there are no windows. The answer is $A$ if $K = 0$, else 0. It needs special handling
  because the odd chain is empty, and $\mathrm{chain}(m, j)$ assumes at least one node (the
  leading factor $A$).
- $K > N - 2$: more palindromes than windows, answer 0. This also covers $N = 2$ with $K > 0$
  (third sample: $N = 2, K = 1$ gives 0).

**Complexity.** $O(N)$ precomputation plus an $O(N)$ loop.
