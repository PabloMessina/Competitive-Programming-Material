# H. Hazel's Harvest

- Problem: [MOJ, icpc-latam-2026 H](https://moj.naquadah.com.br/treino/problema/?id=icpc-latam-2026%23h-growing_counters) (ICPC Latin America 2026 collection)
- Solution: [`icpc-latam-2026_H_HazelsHarvest.cpp`](../../MOJ/icpc-latam-2026_H_HazelsHarvest.cpp)

**Problem.** $N$ trees are planted: tree $i$ is planted in year $Y_i$, already $H_i$ meters tall,
and grows one meter per year after that. Each of $Q$ independent orders $(K, V)$ asks for the
earliest year in which at least $K$ planted trees are each at least $V$ meters tall. Limits:
$N, Q \le 2 \times 10^5$, $Y, H \le 10^9$, $V \le 10^{18}$, time limit 7 s.

**Tags.** offline queries, sweep, k-th smallest, fenwick tree, binary lifting, binary search.

---

## Summary: the key points

1. **Each order is a K-th smallest.**
   - For a fixed $V$, tree $i$ counts from year $r_i = \max(Y_i,\ Y_i + V - H_i)$ on, and keeps
     counting forever.
   - The answer is the $K$-th smallest $r_i$.

2. **Two groups.**
   - $H_i \ge V$ (tall when planted): $r_i = Y_i$.
   - $H_i < V$ (has to grow): $r_i = c_i + V$, with $c_i = Y_i - H_i$ fixed per tree.

3. **Sweep the orders by increasing $V$.**
   - Each tree starts in the first group and moves to the second exactly once, when $V$ passes
     $H_i$.
   - Each group is a Fenwick tree of 0/1 counts over its trees in sorted order. `lower_bound(j)`
     finds the $j$-th smallest of a group in $O(\log N)$ with binary lifting.

4. **K-th smallest of two sorted groups: binary search, not ternary search.**
   - $\text{answer} = \min_x \max(A_x, B_{K-x})$: take $x$ from one group and $K - x$ from the
     other.
   - $A_x$ goes up and $B_{K-x}$ goes down, so binary search the first $x$ where
     $A_x \ge B_{K-x}$. Repeated values make ternary search fail.
   - $O((N + Q) \log^2 N)$ in total.

---

## In depth

### 1. Each order is a K-th smallest

Fix an order $(K, V)$ and look at one tree. In year $t$ it counts toward the order if it is
planted ($t \ge Y_i$) and tall enough ($H_i + t - Y_i \ge V$, i.e. $t \ge Y_i + V - H_i$). So it
counts from year

$$r_i = \max(Y_i,\ Y_i + V - H_i) = Y_i + \max(0,\ V - H_i)$$

on, and never stops counting, because trees only grow. The number of trees that count in year
$t$ is the number of $r_i \le t$, so the earliest year with at least $K$ of them is the
**$K$-th smallest $r_i$**.

### 2. Two groups

The max in $r_i$ splits the trees by whether they are tall enough when planted:

| Group | Condition | $r_i$ |
|---|---|---|
| $A$: tall when planted | $H_i \ge V$ | $Y_i$ (does not depend on $V$) |
| $B$: has to grow | $H_i < V$ | $c_i + V$, with $c_i = Y_i - H_i$ |

Group $B$'s values are fixed numbers $c_i$ all shifted by the same $V$, so the shift does not
change their order. Note that $c_i$ can be negative.

### 3. Sweep the orders by increasing $V$

A tree is in $A$ while $V \le H_i$ and in $B$ once $V > H_i$. So if the orders are processed by
increasing $V$ (offline, saving each answer at its original index), every tree:

- starts in $A$,
- moves to $B$ exactly once, when $V$ first goes above $H_i$,
- never moves back.

Sort the trees by $H$ and keep a pointer: before answering an order, move every tree with
$H_i < V$ to $B$. That is $N$ moves in total. A tree with $H_i = V$ can be in either group:
then $c_i + V = Y_i - H_i + V = Y_i$, so both formulas give the same year.

**Storing the groups.** Sort all trees by $Y$ once: a tree's rank in that order is its slot in
Fenwick tree $A$, which stores 1 at the slot while the tree is in group $A$ and 0 otherwise.
Fenwick tree $B$ is the same over the trees sorted by $c$. Moving a tree is $-1$ in one and
$+1$ in the other. The trees' values never go into the Fenwick trees, only counts, so values up
to $10^{18}$ cause no trouble.

**The $j$-th smallest of a group.** It is the tree at the smallest slot whose prefix count
reaches $j$. `lower_bound(j)` in `Data_Structures/fenwick_tree.cpp` finds that slot by
**binary lifting**: cell `t[pos + 2^b]` holds the count of exactly the $2^b$ slots after `pos`,
so it walks down the powers of 2 and skips every block whose count is still below $j$, in
$O(\log N)$. A binary search over `query()` would also work, but costs $O(\log^2 N)$.

### 4. The K-th smallest of two sorted groups

Let $A_1 \le A_2 \le \ldots$ be group $A$'s values sorted and $B_1 \le B_2 \le \ldots$ group
$B$'s (already shifted by $V$). Choosing the $K$ smallest of the union means taking the $x$
smallest of $A$ and the $K - x$ smallest of $B$ for some $x$, so

$$K\text{-th smallest} = \min_x f(x), \qquad f(x) = \max(A_x,\ B_{K-x}),$$

with $A_0 = B_0 = -\infty$ ("take nothing from that group"). For any $x$, the largest of the
$K$ chosen values is at least the true $K$-th smallest, and for the right $x$ (the number of
$A$'s among the true $K$ smallest) it is exactly that.

**The range of $x$.** You cannot take more from a group than it holds: $x \le |A|$ and
$K - x \le |B|$, so $x \in [\max(0, K - |B|),\ \min(K, |A|)]$.

**Binary search on the crossing.** As $x$ grows, $A_x$ goes up and $B_{K-x}$ goes down, so
$A_x - B_{K-x}$ is non-decreasing. Binary search the first $x^*$ with $A_{x^*} \ge B_{K-x^*}$
(or one past the end if there is none). Before $x^*$, $f(x) = B_{K-x}$, which is going down.
From $x^*$ on, $f(x) = A_x$, which is going up. So the minimum is $f(x^*)$ or $f(x^* - 1)$.

**Why not ternary search.** $f$ is valley-shaped, so ternary search is tempting, but it needs a
*strict* valley. Repeated values (several trees with the same $Y$, or the same $c$) create flat
stretches away from the minimum, such as

$$f = 4,\ 5,\ 5,\ 5 \quad \text{over } x \in [12, 15].$$

Ternary search probes $x = 13$ and $14$, sees $5 = 5$, discards $x = 12$ (the minimum) and
answers 5 instead of 4. This exact case comes from a test with 19 trees. On 1,500 random tests
with many repeated values, a ternary-search version of the solution was wrong on 74, while the
binary-search version matched a brute force on all of them.

### 5. Trace (sample 1)

Trees $(Y, H)$: $(1, 5)$, $(6, 10)$, $(3, 2)$, so $c = -4, -4, 1$. The orders sorted by $V$:

| Order $(K, V)$ | Moved to $B$ | $A$ sorted | $B$ sorted ($c + V$) | $x$ range | $f(x)$ | Answer |
|---|---|---|---|---|---|---|
| $(3, 1)$ | none | $1, 3, 6$ | empty | $[3, 3]$ | $f(3) = \max(6, -\infty) = 6$ | 6 |
| $(2, 4)$ | tree 3 ($H = 2$) | $1, 6$ | $5$ | $[1, 2]$ | $f(1) = \max(1, 5) = 5$, $f(2) = \max(6, -\infty) = 6$ | 5 |
| $(1, 11)$ | trees 1, 2 ($H = 5, 10$) | empty | $7, 7, 12$ | $[0, 0]$ | $f(0) = \max(-\infty, 7) = 7$ | 7 |

Printed in input order, the answers are 5, 7, 6, which matches the expected output.

### 6. Complexity

- **Time.** Sorting is $O(N \log N + Q \log Q)$. Each order does $O(\log N)$ binary-search
  steps, and each step calls `lower_bound` twice in $O(\log N)$, so
  $O((N + Q) \log^2 N)$ overall. With $N = Q = 2 \times 10^5$ it runs in about 0.1 s, far below
  the 7 s limit.
- **Memory.** $O(N + Q)$.

---

## Implementation notes

- **64-bit values.** $c_i + V$ reaches about $10^{18} + 10^9$, and $V$ itself goes up to
  $10^{18}$: both fit in a `long long`. $-\infty$ is `LLONG_MIN`, which is only compared,
  never added to.
- **$H < V$ or $H \le V$** both work when moving trees to group $B$: a tree with $H = V$ gets
  the same year $Y = c + V$ in either group. Sample 2's third order ($K = 1$, $V = 8$, both trees
  with $H = 8$, answer 5) is exactly that boundary case.
- **Slots are 1-indexed** (Fenwick tree), so the tree at slot $s$ is `byY[s - 1]` or
  `byC[s - 1]`.
- **Offline answers.** The orders are processed in $V$ order but printed in input order, so
  each answer is stored at its original index.
- **Library code.** The Fenwick tree is a trimmed copy of `Data_Structures/fenwick_tree.cpp`,
  with `update` and `lower_bound`.
