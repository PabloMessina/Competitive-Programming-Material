# F. Modulo and Counting

- Problem: [Codeforces 2278 F](https://codeforces.com/contest/2278/problem/F) (Codeforces Round 1131, Div. 3)
- Solution: [`2278F_ModuloAndCounting.cpp`](../../Codeforces/2278F_ModuloAndCounting.cpp)
- Official editorial: [blog entry 158300](https://codeforces.com/blog/entry/158300)

**Problem.** Given $n$ and $m$, count the arrays $a$ of length $n$ with
$m + 2 \ge a_1 \ge a_2 \ge \cdots \ge a_n \ge 1$ and
$(a_1 \bmod a_2) + (a_2 \bmod a_3) + \cdots + (a_{n-1} \bmod a_n) = m$, modulo $998\,244\,353$.
Limits: $2 \le n \le 4000$, $1 \le m \le 4000$, and the sums of $n$ and of $m$ over all tests are
each at most 4000.

**Tags.** dp, math, number theory, telescoping sums, prefix sums.

---

## Summary: the key points

The solution has two blocks. **Block A** assumes one structural claim and counts with it, which
needs only a simple DP. **Block B** proves the claim.

### Block A: counting, assuming the claim

1. **The claim: good arrays are "slow chains" from $m+2$ to 2, followed by 1s.**
   - An array is good if and only if, for some $j \in [2, n]$:
     $a_1 = m+2$, $a_j = 2$, $a_k = 1$ for every $k > j$, and every step before $j$ is
     **slow**: $a_{i+1} \le a_i < 2a_{i+1}$.
   - Example ($n = 3$, $m = 1$): $[3, 2, 1]$, $[3, 2, 2]$, $[3, 3, 2]$.

2. **Count slow chains with a DP over (length, last value).**
   - $dp[i][v]$ is the number of slow chains of length $i$ that start at $m+2$ and end at $v$.
   - $dp[1][m+2] = 1$, and $dp[i][v] = \sum_{x = v}^{\min(2v-1,\, m+2)} dp[i-1][x]$.
   - $\text{answer} = \sum_{i=2}^{n} dp[i][2]$. The tail of 1s is forced, so it adds no choices.

3. **Prefix sums give $O(nm)$.**
   - Each entry is a range sum over the previous row, so it takes $O(1)$.
   - Only one row is kept at a time, so memory is $O(m)$.

### Block B: why the claim is true

4. **A modulo is a subtraction.**
   - $x \bmod y = x - k\,y$ with $k = \lfloor x/y \rfloor$. In a non-increasing array, every
     quotient satisfies $k_i \ge 1$.

5. **The sum telescopes into "total drop minus loss".**
   - $\sum (a_i \bmod a_{i+1}) = (a_1 - a_n) - L$, where $L = \sum (k_i - 1)\,a_{i+1} \ge 0$.
   - The condition becomes $L = a_1 - a_n - m$.

6. **The loss budget is at most 1.**
   - $a_1 \le m+2$ and $a_n \ge 1$ give $L \le 1$, so $L \in \{0, 1\}$.

7. **A step has zero loss exactly when it is slow.**
   - Zero loss means $k_i = 1$, which means $a_{i+1} \le a_i < 2a_{i+1}$.
   - Slow steps never reach 1: from any $v \ge 2$, the next value is at least
     $\lfloor v/2 \rfloor + 1 \ge 2$.

8. **The only affordable lossy step is $2 \to 1$.**
   - A lossy step costs $(k_i - 1)\,a_{i+1} \ge 1$. The budget allows at most one, and it must
     cost exactly 1, so $k_i = 2$ and $a_{i+1} = 1$, which means the step is $2 \to 1$.

9. **Putting it together proves the claim, and forces $a_1 = m+2$.**
   - If $a_n = 2$: $L = 0$, and every step is slow.
   - If $a_n = 1$: the array has to enter 1, and it can only do that with $2 \to 1$, so $L = 1$.
   - In both cases $L = a_1 - a_n - m$ gives $a_1 = m + 2$.

---

## In depth

### Block A: counting, assuming the claim

#### 1. The claim

Call a step $a_i \to a_{i+1}$ **slow** if $a_{i+1} \le a_i < 2a_{i+1}$, that is, if the next value
is more than half the current one.

> **Claim.** An array is good if and only if there is an index $j \in [2, n]$ with
>
> 1. $a_1 = m + 2$;
> 2. every step before position $j$ is slow: $a_{i+1} \le a_i < 2a_{i+1}$ for $1 \le i < j$;
> 3. $a_j = 2$;
> 4. $a_k = 1$ for all $k > j$ (when $j = n$ this tail is empty).

So a good array is a slow chain from $m+2$ down to 2, possibly followed by a run of 1s. The index
$j$ is the position of the **last** 2, so the array determines it and each good array is counted
once. Also $j \ge 2$, because $a_1 = m + 2 \ge 3$. Several 2s in a row are allowed, since
$2 \to 2$ is slow ($2 < 4$).

*Example* ($n = 3$, $m = 1$, so $a_1 = 3$):

| $j$ | Arrays | Why |
|---|---|---|
| 2 | $[3, 2, 1]$ | $3 \to 2$ is slow ($3 < 4$), then the tail $1$ |
| 3 | $[3, 2, 2]$, $[3, 3, 2]$ | from 3 a slow step goes to 2 or 3, and both reach 2 |

That is 3 arrays, which matches the expected output. Their modulo sums are
$1 + 0$, $1 + 0$, and $0 + 1$, all equal to $m = 1$.

#### 2. The DP

With the claim, the problem reduces to counting slow chains:

$$\text{answer} = \sum_{j=2}^{n} \#\{\text{slow chains of length } j \text{ from } m+2 \text{ to } 2\}.$$

**State.** $dp[i][v]$ is the number of slow chains $a_1, \ldots, a_i$ with $a_1 = m + 2$ and
$a_i = v$. Only $2 \le v \le m + 2$ is needed, because slow chains never reach 1 (point 7).

**Base case.** $dp[1][m+2] = 1$; every other entry of row 1 is 0.

**Transition.** Read the slow condition backwards: the value $v$ can follow $x$ exactly when
$v \le x < 2v$, so $x \in [v, 2v - 1]$. Values above $m + 2$ never occur, so

$$dp[i][v] = \sum_{x = v}^{\min(2v - 1,\ m + 2)} dp[i-1][x].$$

**Answer.** A chain that reaches 2 at length $i$ becomes exactly one good array once it is padded
with $n - i$ ones:

$$\text{answer} = \sum_{i=2}^{n} dp[i][2].$$

*Trace* ($n = 3$, $m = 1$; the values are 2 and 3):

| $i$ | $dp[i][2]$ | $dp[i][3]$ | Computation |
|---|---|---|---|
| 1 | 0 | 1 | base case |
| 2 | 1 | 1 | $dp[2][2] = dp[1][2] + dp[1][3]$; $dp[2][3] = dp[1][3]$ |
| 3 | 2 | 1 | $dp[3][2] = 1 + 1$; $dp[3][3] = 1$ |

The answer is $1 + 2 = 3$. The 1 counts $[3, 2, 1]$, and the 2 counts $[3, 2, 2]$ and $[3, 3, 2]$.

#### 3. Prefix sums

Each $dp[i][v]$ is a contiguous range sum of row $i - 1$. Build the prefix sums of row $i - 1$
once; then every entry costs $O(1)$. That is $O(m)$ per row and $O(nm)$ per test. Since
$\sum n, \sum m \le 4000$, the worst case is about $1.6 \cdot 10^7$ operations. Only the previous
row is needed, so memory is $O(m)$.

---

### Block B: why the claim is true

#### 4. A modulo is a subtraction

For positive integers $x \ge y$, the division rule (dividend = quotient × divisor + remainder)
gives

$$x \bmod y = x - k\,y, \qquad k = \left\lfloor \tfrac{x}{y} \right\rfloor \ge 1.$$

Set $k_i = \lfloor a_i / a_{i+1} \rfloor$. The array is non-increasing, so $k_i \ge 1$ for every
step.

*Examples:* $7 \bmod 4 = 7 - 1 \cdot 4 = 3$; $9 \bmod 4 = 9 - 2 \cdot 4 = 1$;
$5 \bmod 5 = 5 - 1 \cdot 5 = 0$.

#### 5. The sum telescopes

Substitute point 4 into each term, and split $k_i a_{i+1}$ into $a_{i+1} + (k_i - 1)\,a_{i+1}$:

$$\sum_{i=1}^{n-1} (a_i \bmod a_{i+1})
= \sum_{i=1}^{n-1} (a_i - a_{i+1}) - \sum_{i=1}^{n-1} (k_i - 1)\,a_{i+1}
= (a_1 - a_n) - L.$$

Call $L = \sum (k_i - 1)\,a_{i+1}$ the **loss**. The good-array condition becomes

$$L = a_1 - a_n - m.$$

**Intuition.** Each step contributes its modulo to the sum. That contribution equals how far the
step falls, minus the step's loss:

$$\text{loss}_i = (a_i - a_{i+1}) - (a_i \bmod a_{i+1}) = (k_i - 1)\,a_{i+1}.$$

If $a_{i+1}$ fits into $a_i$ only once ($k_i = 1$), the whole fall counts. Each extra copy of
$a_{i+1}$ inside $a_i$ is lost.

*Example* ($m = 2$):

| Array | Steps (fall / modulo / loss) | Modulo sum | Good? |
|---|---|---|---|
| $[4, 1]$ | $4 \to 1$: $3 / 0 / 3$ | $0$ | no |
| $[4, 3, 2, 1]$ | $4 \to 3$: $1/1/0$; $3 \to 2$: $1/1/0$; $2 \to 1$: $1/0/1$ | $2$ | yes |

Both arrays fall by 3 in total. The first loses all 3, while the second loses only 1.

#### 6. The loss budget is at most 1

- **Lower bound:** every term $(k_i - 1)\,a_{i+1}$ is $\ge 0$, so $L \ge 0$.
- **Upper bound:** $a_1 \le m + 2$ and $a_n \ge 1$, so $L = a_1 - a_n - m \le (m+2) - 1 - m = 1$.

So $L \in \{0, 1\}$. The unusual cap $m + 2$ in the statement is exactly what makes the budget this
small. The bound $L \ge 0$ also forces $a_n \le a_1 - m \le 2$ and $a_1 \ge m + a_n \ge m + 1$.

#### 7. A step has zero loss exactly when it is slow

Since $a_{i+1} \ge 1$, the loss $(k_i - 1)\,a_{i+1}$ is zero exactly when $k_i = 1$, that is,
$1 \le a_i / a_{i+1} < 2$:

$$a_{i+1} \le a_i < 2a_{i+1}.$$

This is the slow condition from the claim. It can be read two ways:

- **Forward:** from $v$, the next value is in $[\lfloor v/2 \rfloor + 1,\ v]$. For example, from 7
  the next value is 4, 5, 6, or 7.
- **Backward** (the form the DP uses): $v$ can be reached from $[v,\ 2v - 1]$. For example, 4 can be
  reached from 4, 5, 6, or 7.

**Side effect:** from any $v \ge 2$, the smallest slow next value is
$\lfloor v/2 \rfloor + 1 \ge 2$. A chain of slow steps never reaches 1. In particular, $2 \to 1$
is not slow, since $2 < 2 \cdot 1$ is false.

#### 8. The only affordable lossy step is $2 \to 1$

Combine the budget (point 6) with the cost of a lossy step:

- A lossy step has $k_i \ge 2$, so it costs $(k_i - 1)\,a_{i+1} \ge a_{i+1} \ge 1$.
- **At most one lossy step:** two of them would cost at least 2, which is more than the budget.
- **It costs exactly 1:** $(k_i - 1)\,a_{i+1} = 1$ with both factors positive integers forces
  $k_i = 2$ and $a_{i+1} = 1$.
- **So it is $2 \to 1$:** $\lfloor a_i / 1 \rfloor = 2$ means $a_i = 2$.

| Step | $k$ | Loss | Within budget? |
|---|---|---|---|
| $8 \to 3$ | 2 | 3 | no |
| $5 \to 2$ | 2 | 2 | no |
| $3 \to 1$ | 3 | 2 | no |
| $2 \to 1$ | 2 | 1 | yes |

After the array reaches 1 it stays at 1, since it is non-increasing and $\ge 1$, and the steps
$1 \to 1$ have zero loss. So the lossy step, if there is one, is followed only by 1s.

#### 9. Putting it together

**Good $\Rightarrow$ the claim's shape.** By point 6, $a_n \in \{1, 2\}$.

- **$a_n = 2$:** the array never reaches 1, so it has no lossy step (point 8) and $L = 0$. Every
  step is slow. Take $j = n$.
- **$a_n = 1$:** the array must enter 1 at some step. Slow steps cannot do that (point 7), so that
  step is the lossy step, which must be $2 \to 1$ (point 8). Then $L = 1$, every other step is
  slow, and the rest of the array is 1s. Take $j$ to be the position of that last 2.

In both cases $L = a_1 - a_n - m$ gives $a_1 = m + 2$.

**The claim's shape $\Rightarrow$ good.** Use modulo sum $= a_1 - a_n - L$:

- $j = n$: all steps are slow, so the sum is $(m + 2) - 2 - 0 = m$.
- $j < n$: the only lossy step is $2 \to 1$, with loss 1, so the sum is $(m + 2) - 1 - 1 = m$.

**Why $a_1 = m + 1$ never works.** With $a_n = 2$ it would need $L = -1$, which is impossible
because losses are never negative. With $a_n = 1$ it would need $L = 0$, which is impossible
because entering 1 always costs at least 1. This is why the DP starts only at $m + 2$. Seeding
$m + 1$ as well would overcount. For example, with $m = 1$ it would count $[2, 1, 1]$, whose
modulo sum is 0.

---

## Implementation notes

- **First attempt (too slow).** A direct DP over (position, previous value, remaining sum), trying
  every next value, is correct. But it has about $n \cdot m^2 \approx 6 \cdot 10^{10}$ states, and
  a range-sum structure doesn't help, because $x \bmod k$ depends on both endpoints. The telescoping
  in point 5 is what collapses the "remaining sum" dimension.
- The loop over lengths builds the prefix sums of the previous row **before** overwriting `dp`:
  ```cpp
  rep(i, 2, n + 1) {
      rep(v, 2, S + 1) pref[v] = (pref[v-1] + dp[v]) % MOD;
      rep(v, 2, S + 1) dp[v] = (pref[min(2*v - 1, S)] - pref[v-1] + MOD) % MOD;
      ans = (ans + dp[2]) % MOD;
  }
  ```
- The official solution updates `dp` in place with a sliding window instead of a prefix array.
  That works because the new `dp[v]` reads only old values at indices $\ge v$, and the loop moves
  left to right.
- Checked against brute force for all $n \le 10$, $m \le 8$, and against the official code on
  random tests and $n = m = 4000$ (about 0.07 s).
