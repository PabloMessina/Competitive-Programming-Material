# E. Thief in a Shop

- Problem: [Codeforces 632 E](https://codeforces.com/problemset/problem/632/E) (Educational Codeforces Round 9)
- Solution: [`632E_ThiefInAShop.cpp`](../../Codeforces/632E_ThiefInAShop.cpp)
- Official editorial: [blog entry 43493](https://codeforces.com/blog/entry/43493)

**Problem.** There are $n$ kinds of products, with infinitely many of each, and kind $i$ costs
$a_i$. The thief takes **exactly** $k$ products. Print every possible total cost in increasing
order. Limits: $1 \le n, k \le 1000$, $1 \le a_i \le 1000$.

**Tags.** dp, unbounded knapsack, min-count DP, shift by minimum, math.

---

## Summary: the key points

1. **The totals lie in a range of size at most $10^6$.**
   - Every total is between $k \cdot a_{\min}$ and $k \cdot a_{\max} \le 10^6$.
   - A knapsack over (number of products, total) would be about $1000 \cdot 10^6 = 10^9$ states,
     which is too slow. The "exactly $k$" dimension has to go.

2. **Shift every price by the minimum.**
   - Let $m = a_{\min}$ and write each price as $m + v$, where $v = a_i - m \ge 0$ is its
     **surcharge**.
   - Any $k$ products cost $k \cdot m + s$, where $s$ is the sum of their surcharges.

3. **"Exactly $k$" becomes "at most $k$".**
   - The cheapest product has surcharge 0, so it can fill any unused slot without changing $s$.
   - So $s$ is reachable with exactly $k$ products $\iff$ it is reachable with **at most** $k$
     products that have a positive surcharge.

4. **Min-count DP over $s$ alone.**
   - $dp[s]$ is the fewest products whose surcharges sum to $s$.
   - $dp[0] = 0$, and $dp[s] = \min_{v \le s} \big(dp[s - v] + 1\big)$ over the positive surcharges $v$.
   - Answer: print $k \cdot m + s$ for every $s$ with $dp[s] \le k$.

5. **Loop order and a bound make it fast.**
   - Put the surcharges in the outer loop, from smallest to largest, and stop the inner loop at
     $k \cdot v$.
   - The total work is $k \cdot \sum v \lesssim 5 \cdot 10^8$ in the worst case; in practice it
     runs in about 0.1 s.

---

## In depth

### 1. Why the direct knapsack is too slow

"Can total $c$ be made with exactly $j$ products?" is a natural state, $(j, c)$. With
$c \le k \cdot a_{\max} \le 10^6$ and $j \le k \le 1000$, that is about $10^9$ states, which is too
slow and too large. Only the sums need to be tracked; the cardinality constraint is what blows up.

### 2. Shift by the minimum

Let $m$ be the cheapest price. Every price is $m$ plus a surcharge:

| Price (sample 3) | Surcharge $v = a_i - 3$ |
|---|---|
| 3 | 0 |
| 5 | 2 |
| 11 | 8 |

Each of the $k$ products contributes $m$ to the total, whichever kind it is, so

$$\text{total} = k \cdot m + s, \qquad s = \text{sum of the chosen surcharges}.$$

For example, with $k = 3$, taking $5, 5, 11$ costs $9 + (2 + 2 + 8) = 21$. Now the question is
which values of $s$ are reachable.

### 3. "Exactly $k$" becomes "at most $k$"

Suppose $s$ can be built from $c \le k$ products with positive surcharges. Add $k - c$ copies of
the cheapest product: they add 0 to $s$, and the knapsack now holds exactly $k$ products.
Conversely, any choice of exactly $k$ products contains at most $k$ products with a positive
surcharge. So:

> $s$ is reachable with exactly $k$ products $\iff$ $s$ can be built from at most $k$ products
> with positive surcharges.

*Example:* $s = 8$ needs only the 11. Fill the other two slots with 3s: $11 + 3 + 3 = 17 = 9 + 8$.

The same idea is used in combinatorics to remove lower bounds: to count
$x_1 + \cdots + x_n = N$ with every $x_i \ge c$, substitute $y_i = x_i - c \ge 0$. It is also
the reverse of a common reduction that turns "at most $k$" into "exactly $k$" by adding
zero-weight dummy items.

### 4. The min-count DP

"At most $k$" only needs the **fewest** products for each $s$. This is the minimum-coins
problem from coin change.

**State.** $dp[s]$ is the minimum number of products whose surcharges sum to $s$.

**Base case.** $dp[0] = 0$. Every other entry starts at "infinity".

**Recurrence.** Ask which product went in last. If its surcharge is $v$, the others built
$s - v$:

$$dp[s] = \min_{v \in V,\ v \le s} \big( dp[s - v] + 1 \big),$$

where $V$ is the set of positive surcharges. Here $v$ is not part of the state; it is the choice
being minimized over. Every $v \ge 1$, so $dp[s]$ only depends on smaller indices and there is
no cycle.

**Answer.** $s$ is valid when $dp[s] \le k$; print $k \cdot m + s$. Increasing $s$ gives
increasing totals.

**Infinity $= k + 1$.** An unreachable $s$ is never updated, so it keeps $k + 1$ and fails the
test automatically. The value $k + 1$ is above $k$, and $dp[s - v] + 1 = k + 2$ cannot overflow.
`INT_MAX` would overflow on the $+1$, wrap to a negative number, and win the `min`.

*Trace* (sample 3: $k = 3$, $V = \lbrace 2, 8 \rbrace$; only even $s$ are reachable):

| $s$ | 0 | 2 | 4 | 6 | 8 | 10 | 12 | 14 | 16 | 18 | 24 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| $dp[s]$ | 0 | 1 | 2 | 3 | 1 | 2 | 3 | **4** | 2 | 3 | 3 |

For example, $dp[8] = \min(dp[6] + 1, dp[0] + 1) = \min(4, 1) = 1$. Every listed $s$ except 14
has $dp[s] \le 3$ (14 needs $8 + 2 + 2 + 2$). Adding 9 gives
`9 11 13 15 17 19 21 25 27 33`, which matches the expected output.

### 5. Loop order and the $k \cdot v$ bound

The recurrence loops over $s$ outside and $v$ inside. Swapping them gives the usual unbounded
knapsack:

```cpp
for (int v : V)                      // increasing
    for (int j = v; j <= k * v; j++)
        dp[j] = min(dp[j], dp[j - v] + 1);
```

Both orders compute the same table. The swapped order allows the bound $j \le k \cdot v$:
at most $k$ products, each with surcharge at most $v$, sum to at most $k \cdot v$. Combinations
whose largest surcharge is smaller than $v$ were already handled by earlier, smaller surcharges.
Inside the loop for $v$, increasing $j$ lets $v$ be reused, which is what makes it unbounded.

**Complexity.** $O(k \cdot \sum v)$ time over the distinct surcharges, at most about
$1000 \cdot 499500 \approx 5 \cdot 10^8$ simple operations. Memory is
$O(k \cdot (a_{\max} - m)) \le 10^6$ ints.

---

## Implementation notes

- Sort the prices and remove duplicates first. Each kind has infinite supply, so a repeated
  price adds nothing, and afterwards every surcharge except the first is positive.
- The cheapest price has surcharge 0, so it gets no update loop; it only acts as the filler.
- **Alternative (editorial).** Build the polynomial $P(x) = \sum x^{a_i}$ and compute $P(x)^k$
  with FFT or NTT. The exponents with a nonzero coefficient are the totals. With NTT, use two or
  three moduli, because a nonzero coefficient can be $0$ modulo one prime. That is more code for
  the same answer.
- Checked against all three samples, against a brute force on 300 random small inputs, and on
  the worst case $n = k = 1000$ with prices $1..1000$ (about 0.1 s with `g++-15 -O2`).
