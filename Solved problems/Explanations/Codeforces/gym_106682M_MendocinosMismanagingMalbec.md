# M. Mendocinos Mismanaging Malbec

- Problem: [Codeforces Gym 106682 M](https://codeforces.com/gym/106682/problem/M) (2026 Argentinian Programming Tournament, TAP)
- Solution: [`gym_106682M_MendocinosMismanagingMalbec.cpp`](../../Codeforces/gym_106682M_MendocinosMismanagingMalbec.cpp)
- Template used: [`segment_tree_lazy.cpp`](../../../Data_Structures/segment_tree_lazy.cpp) (based on AtCoder Library's `lazy_segtree`)

**Problem.** $N$ barrels in a line, barrel $i$ with capacity $A_i$, all initially empty.
$M$ operations ($N, M \le 2 \times 10^5$):

- `1 B V`: pour $V$ liters into barrel $B$. Whatever doesn't fit overflows into $B - 1$, then
  $B - 2$, and so on; overflow from barrel 1 is lost.
- `2 L R`: print the total amount in barrels $L..R$, then empty them.

**Tags.** segment tree, lazy propagation, range assignment, binary search on a segment tree.

---

## Summary: the key points

1. **A pour has a simple shape.**
   - It fills a contiguous block $[l, B]$ completely, partially fills barrel $l - 1$, and leaves
     everything else unchanged.

2. **Both updates are range assignments.**
   - "Fill $[l, B]$ completely" and "empty $[L, R]$" each set every barrel in a range to a fixed
     state. Lazy propagation handles assignments, not only additions.

3. **Store capacity in each node, so "fill completely" is $O(1)$.**
   - Node = $\lbrace \text{fill}, \text{cap}\rbrace$. Capacities never change, so "full" means
     $\text{fill} = \text{cap}$ for the whole node.

4. **Find $l$ by searching down the tree, not with an outer binary search.**
   - Free space in $[l, B]$ grows as $l$ moves left, so "free space $\le V$" is monotone.
   - The tree search `min_left` finds $l$ in $O(\log N)$, instead of $O(\log^2 N)$ for binary
     search over range queries. No separate set of "full intervals" is needed.

5. **Each operation is a few $O(\log N)$ calls.**
   - Pour: `min_left`, then fill $[l, B]$, then set barrel $l - 1$.
   - Take: range sum of fill, then empty $[L, R]$.

---

## In depth

### 1. A pour has a simple shape

Pouring into barrel $B$ goes right to left: barrel $B$ takes what fits, the excess moves to
$B - 1$, and so on. It stops at the first barrel (going left) that has room for whatever is left.
So after a pour:

- a contiguous block of barrels $[l, B]$ is **completely full**;
- barrel $l - 1$ receives the leftover, which fits in it, so it's **partially filled**;
- if $l = 1$ (barrel 1 overflowed), the leftover falls to the floor.

Barrels outside $[l - 1, B]$ are untouched.

### 2. Both updates are range assignments

The operations change the barrels in three ways:

- fill a range completely (a pour);
- set one barrel to a specific amount (the partial barrel of a pour);
- empty a range (a take).

A common misconception is that a lazy segment tree only supports "add $\delta$ to a range". In
fact a lazy tag can be any update, as long as:

1. applying it to a node gives the node's new value in $O(1)$, without visiting the children;
2. two pending tags can be combined into one.

"Set to empty" and "set to full" satisfy both. For combining, the newer assignment simply
overwrites the older one.

### 3. Store capacity in each node, so "fill completely" is $O(1)$

Each node stores $\lbrace \text{fill}, \text{cap}\rbrace$ for its range: how much malbec its barrels hold, and
their total capacity. Merging two nodes adds both fields. Capacities never change, so the tags are:

| Tag | Effect on a node | Meaning |
|---|---|---|
| `NONE` | unchanged | no pending update |
| `EMPTY` | $\lbrace 0, \text{cap}\rbrace$ | every barrel in the range is empty |
| `FULL` | $\lbrace \text{cap}, \text{cap}\rbrace$ | every barrel in the range is full |

Combining tags: the newer one wins, unless it is `NONE`.

A separate `NONE` value matters. A template that uses `lazy == 0` to mean "nothing pending"
breaks with assignments, because "set to 0" is a real update.

The free space of a node is $\text{cap} - \text{fill}$, so it doesn't need its own field.

### 4. Find $l$ by searching down the tree

We need the smallest $l$ such that barrels $[l, B]$ together have **at most $V$** free space.
Then all of them get filled, and the leftover $V - \text{free}(l..B)$ goes into barrel $l - 1$.
By the choice of $l$, adding barrel $l - 1$ would exceed $V$, so the leftover fits in it.

The condition is monotone: moving $l$ left only adds barrels, so free space only grows. That
means "the smallest $l$" can be found by a search that walks down the tree, as in
`min_left(B + 1, pred)` from AtCoder Library, with the predicate
$\text{pred}(\text{node}) = (\text{cap} - \text{fill} \le V)$. It costs $O(\log N)$.

Compared with alternatives:

- **Binary search on $l$** with a range query per step: $O(\log^2 N)$ per pour.
- **An ordered set of full intervals**, skipping over full blocks: unnecessary, because the tree
  already knows where the free space is (and keeping the set in sync with the tree is error-prone).

The `min_left` call also covers the case where barrel $B$ alone has enough room: the free space of
$[B, B]$ already exceeds $V$, so $l = B + 1$, nothing gets filled completely, and the whole $V$
goes into barrel $B$ as a partial fill.

### 5. Each operation is a few $O(\log N)$ calls

With 0-indexed barrels and half-open ranges $[l, r)$, as in the template:

```cpp
// pour V into barrel b (0-indexed)
int l = st.min_left(b + 1, [&](Node x) { return x.cap - x.fill <= V; });
Node seg = st.prod(l, b + 1);
ll leftover = V - (seg.cap - seg.fill);
st.apply(l, b + 1, FULL);
if (l > 0 && leftover > 0) {
    Node x = st.get(l - 1);
    st.set(l - 1, {x.fill + leftover, x.cap});
}

// take barrels L..R (1-indexed)
cout << st.prod(L - 1, R).fill << '\n';
st.apply(L - 1, R, EMPTY);
```

Totals can reach $2 \times 10^5 \times 10^9 = 2 \times 10^{14}$, so `fill`, `cap` and `V` are
`long long`. Total complexity: $O((N + M) \log N)$.

### Walking through the sample

Capacities `3 15 2 10 6` (barrels 1 to 5).

| Operation | What happens | Fill after |
|---|---|---|
| `1 4 7` | barrel 4 has 10 free, takes all 7 | `0 0 0 7 0` |
| `1 5 10` | free space from the right: 6, then $6 + 3 = 9 \le 10$, then $9 + 2 = 11 > 10$. So barrels 4–5 fill, and the leftover $10 - 9 = 1$ goes into barrel 3 | `0 0 1 10 6` |
| `2 3 4` | prints $1 + 10 = $ **11**, empties barrels 3–4 | `0 0 0 0 6` |
| `2 1 5` | prints **6**, empties everything | `0 0 0 0 0` |
| `1 1 5` | barrel 1 fills (3 liters), the other 2 fall to the floor | `3 0 0 0 0` |
| `1 2 12` | barrel 2 has 15 free, takes all 12 | `3 12 0 0 0` |
| `2 1 2` | prints $3 + 12 = $ **15** | `0 0 0 0 0` |
