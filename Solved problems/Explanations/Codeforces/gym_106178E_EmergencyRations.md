# E. Emergency Rations

- Problem: [Codeforces Gym 106178 E](https://codeforces.com/gym/106178/problem/E) (2025-2026 ICPC Latin American Regional Programming Contest)
- Solution: [`gym_106178E_EmergencyRations.cpp`](../../Codeforces/gym_106178E_EmergencyRations.cpp)
- Statements: [contest PDF](https://scorelatam.naquadah.com.br/latam-2025/contest.pdf)

**Problem.** A supply of ration boxes starts empty. There are $Q$ changes, each adding a box with
$c$ rations ($+c$) or removing an existing box with exactly $c$ rations ($-c$). Each day you
either (1) empty one non-empty box completely, or (2) take one ration from every non-empty box.
After each change, print the minimum number of days needed to empty all boxes.
Limits: $1 \le Q \le 3 \cdot 10^5$, $1 \le |X_i| \le 10^9$, and every removal is valid.

**Tags.** segment tree lazy, range add, range min, coordinate compression, offline, greedy, math.

---

## Summary: the key points

1. **Only the number of action-2 days matters.**
   - With $t$ action-2 days, boxes with $c \le t$ are emptied by them, and every box with $c > t$
     needs its own action-1 day.
   - $\text{answer} = \min_{t \ge 0} f(t)$, where $f(t) = t + \lvert \lbrace \text{boxes with } c > t \rbrace \rvert$.

2. **Only a few values of $t$ need checking.**
   - Between two consecutive box sizes, $f$ only grows, so an optimal $t$ is 0 or a box size.
   - Every $f(t)$ is the cost of a real plan, so extra candidates are harmless.

3. **A change to the supply is a prefix update on $f$.**
   - A box of size $c$ adds 1 to $f(t)$ exactly for $t < c$.
   - $+c$ adds $+1$ to those $t$, $-c$ adds $-1$, and the answer is the global minimum.

4. **Offline coordinate compression and a lazy segment tree.**
   - Candidates are 0 and every $|X_i|$, sorted. Leaf $i$ starts at $f(t_i) = t_i$.
   - Each change is one range add on $[0, \text{idx}(c))$, and the answer is the root's minimum.
     $O(Q \log Q)$ in total.

---

## In depth

### 1. Only the number of action-2 days matters

Fix any plan and let $t$ be the number of days it uses action 2.

- A box with $c \le t$ is emptied by the action-2 days alone.
- A box with $c > t$ still has rations after them, so some action-1 day must empty it. One
  action-1 day empties one box, so these boxes need at least one day each.

So every plan with $t$ action-2 days takes at least

$$f(t) = t + \lvert \lbrace \text{boxes with } c > t \rbrace \rvert$$

days. The plan "empty every box with $c > t$ using action 1, then use action 2 for $t$ days"
takes exactly $f(t)$ days, so

$$\text{answer} = \min_{t \ge 0} f(t).$$

**Intuition.** Big boxes are emptied one per day; small boxes are worn down together. The only
decision is where to draw the line between big and small.

*Example* (boxes $\lbrace 1, 2, 2, 7 \rbrace$):

| $t$ | 0 | 1 | 2 | 7 |
|---|---|---|---|---|
| $\lvert \lbrace c > t \rbrace \rvert$ | 4 | 3 | 1 | 0 |
| $f(t)$ | 4 | 4 | **3** | 7 |

The best plan is $t = 2$: empty the 7 with action 1, then two days of action 2 finish the rest.

**Equivalent view.** Sort the boxes as $c_1 \ge c_2 \ge \cdots \ge c_n$. Emptying the $j$ largest
with action 1 and wearing down the rest takes $j + c_{j+1}$ days (with $c_{n+1} = 0$), so the
answer is $\min_j (j + c_{j+1})$.

### 2. Only a few values of $t$ need checking

Let $s < s'$ be consecutive box sizes. For $s \le t < s'$, the count $\lvert \lbrace c > t \rbrace \rvert$ is the
same, but $t$ grows, so $f(t)$ is smallest at $t = s$. For $t$ above the largest size, $f(t) = t$
keeps growing. So an optimal $t$ is either 0 or one of the current box sizes.

**Extra candidates are harmless.** For every $t \ge 0$, $f(t)$ is the cost of the plan from point 1,
so $f(t) \ge \text{answer}$. A minimum over a larger set of $t$ values gives the same result, as
long as the set contains 0 and the current sizes. This allows one fixed set of candidates
for all queries: sizes of boxes that were removed, or will be added later, may stay in it.

### 3. A change to the supply is a prefix update on $f$

A box of size $c$ contributes 1 to $f(t)$ exactly when $t < c$. So:

- **Adding** a box of size $c$: $f(t) \mathrel{+}= 1$ for every $t < c$.
- **Removing** a box of size $c$: $f(t) \mathrel{-}= 1$ for every $t < c$.
- **Query:** the answer is $\min_t f(t)$.

With the candidates sorted, "$t < c$" is a **prefix** of the array. This is the classic workload of
a segment tree with lazy range add and range min.

### 4. Offline coordinate compression and a lazy segment tree

Box sizes go up to $10^9$, but all operations are known upfront. So the solution reads them
first and builds the sorted, deduplicated candidate list $t_0 = 0 < t_1 < \cdots < t_{m-1}$, with
$m \le Q + 1$.

- **Initial leaves.** With no boxes, $f(t) = t$, so leaf $i$ starts at $t_i$.
- **Update.** For $X = \pm c$, let $i$ be the index of $c$ (found with `lower_bound`). The
  candidates with $t < c$ are exactly the indices $[0, i)$, so the code calls
  `apply(0, i, ±1)`. $i \ge 1$, because $c \ge 1 > 0 = t_0$.
- **Query.** The answer is the minimum over all leaves, `all_prod()`, which is the root.

*Trace* (sample 1: `+1 +2 +2 +7 -2 +10 -1 -2`, candidates $\lbrace 0, 1, 2, 7, 10 \rbrace$):

| After | Boxes | $f(0)$ | $f(1)$ | $f(2)$ | $f(7)$ | $f(10)$ | Answer |
|---|---|---|---|---|---|---|---|
| +1 | {1} | 1 | 1 | 2 | 7 | 10 | 1 |
| +2 | {1,2} | 2 | 2 | 2 | 7 | 10 | 2 |
| +2 | {1,2,2} | 3 | 3 | 2 | 7 | 10 | 2 |
| +7 | {1,2,2,7} | 4 | 4 | 3 | 7 | 10 | 3 |
| −2 | {1,2,7} | 3 | 3 | 3 | 7 | 10 | 3 |
| +10 | {1,2,7,10} | 4 | 4 | 4 | 8 | 10 | 4 |
| −1 | {2,7,10} | 3 | 4 | 4 | 8 | 10 | 3 |
| −2 | {7,10} | 2 | 3 | 4 | 8 | 10 | 2 |

The answers are `1 2 2 3 3 4 3 2`, which matches the expected output. The candidate 10 is in the
tree from the start, even though box 10 only appears at step 6. Before that, $f(10) = 10$ is a
valid but bad plan, so it never affects the minimum.

**Complexity.** Sorting the candidates is $O(Q \log Q)$. Each change is one range add and one
$O(1)$ root read on a tree with at most $Q + 1$ leaves, so the total is $O(Q \log Q)$.

---

## Implementation notes

- The tree is the AtCoder-style `LazySegTree` from `Data_Structures/segment_tree_lazy.cpp`,
  trimmed to the constructor, range `apply`, and `all_prod` (no point updates, range queries,
  or binary searches). Its ranges are half-open, so "indices $< i$" is `apply(0, i, f)`.
- Range add + range min:
  - `op = min`, `e = LLONG_MAX`.
  - `mapping(f, x) = x + f`: adding $f$ to every element of a node shifts its minimum by $f$,
    so the node length isn't needed (unlike range add + range sum).
  - `composition(f, g) = f + g`, `id = 0`.
- `LLONG_MAX + f` can't overflow: $e()$ only fills the padding leaves beyond $m$, and an update
  is only applied to nodes fully inside $[0, i) \subseteq [0, m)$, so padding never receives a
  nonzero add.
- `cin >> int` reads `+7` and `-2` directly as signed integers.
- An earlier version used a recursive lazy segment tree with an `INT_MAX` sentinel candidate
  and a hash map for compression. With half-open ranges and `lower_bound`, neither is needed.
- Checked against both samples, a brute force on 400 random tests, and a random test with
  $Q = 3 \cdot 10^5$ (about 0.13 s with `g++-15 -O2`).
