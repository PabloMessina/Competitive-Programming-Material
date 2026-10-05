# D. Digit One Dilemma

- Problem: [Codeforces Gym 106682 D](https://codeforces.com/gym/106682/problem/D) (2026 Argentinian Programming Tournament, TAP)
- Solution: [`gym_106682D_DigitOneDilemma.cpp`](../../Codeforces/gym_106682D_DigitOneDilemma.cpp)

**Problem.** Banknotes only come in values $1, 11, 111, 1111, \ldots$ (repunits). Given $X$ with
up to 100,001 digits, find the minimum number of banknotes that sum to $X$.

**Tags.** math, repunits, digit sum, big numbers.

---

## Summary: the key points

1. **Repunits have a closed form.**
   - The repunit with $k$ ones is $R_k = 11\ldots1 = \dfrac{10^k - 1}{9}$.
   - Example: $9 \times 111 = 999 = 10^3 - 1$.

2. **Multiplying by 9 turns notes into powers of ten.**
   - If we use $c_k$ notes of $R_k$ and $S = \sum c_k$ notes in total, then
     $$9X + S = \sum_{k \ge 1} c_k \cdot 10^k.$$

3. **Guess $S$, then check it.**
   - For a fixed $S$, the question becomes: can $N = 9X + S$ be written as a sum of exactly $S$
     powers of ten, each at least $10^1$?
   - Every such sum translates back into a valid payment (each $10^k$ is one note $R_k$).
   - The answer is the smallest $S$ that passes the check.

4. **The fewest powers of ten is the digit sum.**
   - $N$ must end in 0 (there is no $10^0$ term: every note has at least one 1).
   - The decimal digits of $N$ use exactly $\mathrm{digitsum}(N)$ powers of ten, and no
     representation uses fewer.

5. **Splits add exactly 9, and land exactly on $S$.**
   - Replacing one $10^k$ by ten $10^{k-1}$ keeps the total and adds 9 terms.
   - $\mathrm{digitsum}(N) \equiv N \equiv S \pmod 9$, so the gap is always a multiple of 9.
   - Final test: $S$ works $\iff$ $N$ ends in 0 **and** $\mathrm{digitsum}(N) \le S$.

6. **Scan $S$ upward, looking only at the last 7 digits.**
   - The answer is below $10^6$, so adding $S$ to $9X$ only changes the last 7 digits, plus a
     carry of at most 1 into the rest.
   - Precompute the digit sums of the high part $H$ and of $H + 1$; each check is then $O(1)$.

---

## In depth

### 1. Repunits have a closed form

Write $R_k$ for the number made of $k$ ones. Multiplying by 9 gives $k$ nines:

$$9 \cdot R_k = \underbrace{99\ldots9}_{k} = 10^k - 1 \quad\Longrightarrow\quad R_k = \frac{10^k - 1}{9}.$$

The banknotes are $R_1 = 1$, $R_2 = 11$, $R_3 = 111$, and so on.

### 2. Multiplying by 9 turns notes into powers of ten

A payment uses $c_k \ge 0$ notes of each $R_k$. Let $S = \sum_k c_k$ be the number of notes,
which is what we want to minimize. Then

$$X = \sum_k c_k R_k = \sum_k c_k \frac{10^k - 1}{9}.$$

Multiply by 9 and expand:

$$9X = \sum_k c_k 10^k - \sum_k c_k = \sum_k c_k 10^k - S
\quad\Longrightarrow\quad
9X + S = \sum_{k \ge 1} c_k \cdot 10^k.$$

The right-hand side is a sum of powers of ten ($c_1$ copies of $10$, $c_2$ copies of $100$, ...),
with exactly $S$ terms in total.

### 3. Guess $S$, then check it

The identity has $S$ on both sides, which looks circular. The way out is to reverse the
direction: **guess** $S$, which fixes the number $N = 9X + S$, and then **check** whether $N$ can
be split into exactly $S$ powers of ten, all at least $10^1$.

The translation works both ways:

- A payment of $X$ with $S$ notes gives such a split of $9X + S$ (point 2).
- A split of $9X + S$ into $S$ powers of ten gives a payment: each $10^k$ is one note $R_k$, and
  running the algebra of point 2 backwards shows the notes sum to $X$.

So the problem is: **find the smallest $S$ such that $9X + S$ is a sum of exactly $S$ powers of
ten, each at least $10^1$.**

*Example* ($X = 14$): guess $S = 4$, so $N = 126 + 4 = 130 = 100 + 10 + 10 + 10$, which is 4
terms. Translating back: $100 \to R_2 = 11$ and each $10 \to R_1 = 1$, so $11 + 1 + 1 + 1 = 14$.

### 4. The fewest powers of ten is the digit sum

**$N$ must end in 0.** Every term is a multiple of 10, so the sum is too. Any $S$ where $9X + S$
doesn't end in 0 is rejected immediately.

**The minimum number of terms is $\mathrm{digitsum}(N)$.**

- *Achievable:* use the decimal digits as the counts. For $N = 130$: one $10^2$ and three
  $10^1$, which is $1 + 3 + 0 = 4$ terms. Because the units digit is 0, no $10^0$ is needed.
- *Optimal:* take any representation. If some $10^k$ appears 10 or more times, merge ten of them
  into one $10^{k+1}$. The total is unchanged and the count drops by 9. Repeat until every power
  appears at most 9 times. That is the decimal representation, which is unique. So every
  representation has **at least** $\mathrm{digitsum}(N)$ terms.

*Example* ($X = 1997$, answer 27): $9X = 17973$ and $N = 17973 + 27 = 18000$, whose digit sum
is 9. So $N$ needs at least 9 terms, but we need exactly 27. Point 5 bridges that gap.

### 5. Splits add exactly 9, and land exactly on $S$

**One split adds 9 terms.** Replace one $10^k$ (with $k \ge 2$) by ten $10^{k-1}$. The total is
the same, since $10^k = 10 \cdot 10^{k-1}$, and the count grows by $10 - 1 = 9$. Starting from
the digits, the reachable counts are
$\mathrm{digitsum}(N),\ \mathrm{digitsum}(N) + 9,\ \mathrm{digitsum}(N) + 18, \ldots$

**$S$ is automatically one of them, if it's large enough.** We need
$S - \mathrm{digitsum}(N)$ to be a non-negative multiple of 9. The "multiple of 9" part is free:

- Any number is congruent to its digit sum mod 9, so $\mathrm{digitsum}(N) \equiv N \pmod 9$.
- $N = 9X + S \equiv S \pmod 9$.

So only the inequality $\mathrm{digitsum}(N) \le S$ needs checking. This is why
"$\mathrm{digitsum}(N) = S$" would be the wrong test. For $X = 10$, no $S$ satisfies the equality,
but $S = 10$ works ($N = 100$, digit sum 1, then one split gives ten $10^1$, i.e. ten notes of 1).

**We never run out of splits.** Splitting can go on until every term is $10^1$, which gives
$N / 10$ terms, the maximum. We need $S \le N/10$, and

$$10S \le 9X + S \iff S \le X,$$

which holds for every $S$ we test, since $S = X$ always works ($X$ notes of 1).

**Final test:**

$$S \text{ works} \iff N = 9X + S \text{ ends in } 0 \ \text{ and } \ \mathrm{digitsum}(N) \le S.$$

*Example* ($X = 1997$, $S = 27$, $N = 18000$): the gap is $27 - 9 = 18$, so two splits.

| Step | Representation of 18000 | Terms |
|---|---|---|
| digits | $1 \cdot 10^4 + 8 \cdot 10^3$ | 9 |
| split $10^4$ | $18 \cdot 10^3$ | 18 |
| split one $10^3$ | $17 \cdot 10^3 + 10 \cdot 10^2$ | 27 |

Back to notes: $17 \times 111 + 10 \times 11 = 1887 + 110 = 1997$, using 27 notes. This differs
from the payment in the problem's note ($1111 + 6 \times 111 + 20 \times 11$), which also uses
27: optimal payments are not unique.

### 6. Scan $S$ upward, looking only at the last 7 digits

**Scan.** Test $S = 1, 2, 3, \ldots$ and stop at the first $S$ that passes. Testing in increasing
order means the first one is the minimum, with no need for binary search or monotonicity.

**The answer is below $10^6$.** $N$ has at most about 100,003 digits, so
$\mathrm{digitsum}(N) \le 9 \times 100{,}003 = 900{,}027$. Among any 10 consecutive values of $S$,
exactly one makes $N$ end in 0. So within 10 steps past 900,027 some $S$ passes.

**Each check is $O(1)$.** A full big-number addition per candidate would cost up to
$10^6 \times 10^5 = 10^{11}$ operations. Instead:

- Split once: $9X = H \cdot 10^7 + lo$, where $lo$ is the last 7 digits (an `int`) and $H$ is
  the rest.
- For $S < 10^6$: $v = lo + S < 10^7 + 10^6$, so the carry into $H$ is **0 or 1**. That's why 7
  digits: $10^7$ is larger than any $S$ we test.
- The digit sum splits over the two parts:
  $$\mathrm{digitsum}(N) = \mathrm{digitsum}(H + \text{carry}) + \mathrm{digitsum}(v \bmod 10^7).$$
- Precompute once:
  - $\mathrm{digitsum}(H)$;
  - $\mathrm{digitsum}(H + 1)$: the $t$ trailing 9s of $H$ become 0s and the next digit grows by 1,
    giving $\mathrm{digitsum}(H) - 9t + 1$. If $H$ is all 9s (or empty), $H + 1 = 10\ldots0$ and
    the digit sum is 1.

**Complexity.** $O(L)$ to compute $9X$ and the two digit sums, plus under $10^6 \times 7$
operations for the scan. It runs in well under 0.01 s at maximum size.

*Example* ($X = 1997$): $9X = 17973$ has fewer than 8 digits, so $H = 0$ and $lo = 17973$. Only
$S \equiv 7 \pmod{10}$ makes $N$ end in 0:

| $S$ | $N = 17973 + S$ | digit sum | passes? |
|---|---|---|---|
| 7 | 17980 | 25 | no ($25 > 7$) |
| 17 | 17990 | 26 | no ($26 > 17$) |
| 27 | 18000 | 9 | **yes** ($9 \le 27$) |

The drop from 26 to 9 comes from the carries in $17990 \to 18000$: the digit sum is not monotone
in $S$, which is why the solution scans instead of trying to compute $S$ directly.

---

## Implementation notes

- Compute $9X$ digit by digit from the least significant end, propagating the carry.
- The scan loop:
  ```cpp
  for (int s = 1; ; s++) {
      int v = lo + s;                 // carry into H is 0 or 1
      int low = v % 10000000;
      if (low % 10 != 0) continue;    // N must end in 0
      int ds = (v >= 10000000 ? ds_h1 : ds_h) + digitsum(low);
      if (ds <= s) { cout << s << '\n'; break; }
  }
  ```
- **Side fact:** the greedy "take as many of the largest repunit as possible" also gives the
  optimal answer (checked against a brute-force DP for every $X$ up to $3 \times 10^6$). It is
  much harder to run fast on a 100,001-digit number, though, because each step is a big-number
  division.
