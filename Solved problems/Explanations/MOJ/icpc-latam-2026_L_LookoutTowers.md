# L. Lookout Towers

- Problem: [MOJ, icpc-latam-2026 L](https://moj.naquadah.com.br/treino/problema/?id=icpc-latam-2026%23l-watchtowers) (ICPC Latin America 2026 collection)
- Solution: [`icpc-latam-2026_L_LookoutTowers.cpp`](../../MOJ/icpc-latam-2026_L_LookoutTowers.cpp)

**Problem.** A tree has $N$ nodes, and some of them have a watchtower (at least two do). Find the
minimum distance between two different towers and the number of unordered pairs of towers at
that distance. Limits: $2 \le N \le 2 \times 10^5$, time limit 1.5 s.

**Tags.** trees, tree DP, DFS, LCA counting, counting pairs.

---

## Summary: the key points

1. **Count every pair at its LCA.**
   - Root the tree at 1. Each pair of towers has exactly one LCA, the highest node on the path
     between them.
   - At its LCA $v$, a pair is either two towers in different child subtrees of $v$, or $v$
     itself plus a tower below it. Both cases only need information from below $v$.

2. **Only the nearest towers of each subtree matter.**
   - If $(a, b)$ is at the global minimum distance $D$, then $a$ is one of the towers closest to
     the LCA within its child subtree. A closer one would give a pair shorter than $D$.
   - So each subtree is summarized by two numbers: $m$, the distance to its nearest tower, and
     $c$, the number of towers at that distance.

3. **Count first, then merge.**
   - $v$ starts as $(0, 1)$ if it is a tower and $(\infty, 0)$ otherwise. Each child is shifted
     to $(m' + 1, c')$.
   - Before merging a child, pair it with what $v$ has so far: distance $m + m' + 1$, with
     $c \cdot c'$ pairs. Then merge: keep the smaller distance, adding the counts on a tie.

4. **No pair is counted twice.**
   - A pair is counted only at its LCA, and only when the later of its two branches is merged.
   - One DFS, $O(N)$ in total.

---

## In depth

### 1. Count every pair at its LCA

Root the tree at node 1. For any two towers $a$ and $b$, the path between them has exactly one
highest node, the one closest to the root: their **lowest common ancestor** (LCA). If each pair
is counted only at its LCA, no pair can be counted twice.

Stand at a node $v$ and ask which pairs have $v$ as their LCA. There are only two shapes:

1. one tower in the subtree of a child $u_1$ and the other in the subtree of a *different*
   child $u_2$;
2. $v$ is a tower, and the other tower is somewhere below it.

Both shapes only involve what is **below** $v$, so the DP never needs to look up through the
parent. An "up" DP over the parent (rerooting) is not needed.

### 2. Only the nearest towers of each subtree matter

**Lemma.** Let $D$ be the global minimum distance, and let $(a, b)$ be a pair at distance $D$
with LCA $v$, where $a$ is in the subtree of child $u$. Then no tower in $u$'s subtree is closer
to $v$ than $a$.

**Proof.** Suppose a tower $a'$ in $u$'s subtree had $\text{dist}(a', v) < \text{dist}(a, v)$.
The towers $a'$ and $b$ are on different branches of $v$ (or $b = v$), so the path between them
goes through $v$:

$$\text{dist}(a', b) = \text{dist}(a', v) + \text{dist}(v, b) < \text{dist}(a, v) + \text{dist}(v, b) = D.$$

That contradicts $D$ being the minimum. $\blacksquare$

So for each subtree we only need:

- $m[u]$: the distance from $u$ to the nearest tower in its subtree ($\infty$ if there are none);
- $c[u]$: the number of towers at exactly that distance.

Every other tower in the subtree is too far away to belong to a minimum pair through $u$, so
forgetting it is safe.

### 3. Computing $(m, c)$ bottom-up

For a node $v$:

1. **Start** with $v$ alone: $(0, 1)$ if $v$ is a tower, otherwise $(\infty, 0)$.
2. **Shift** each child $u$: its towers are one edge farther from $v$, so it contributes
   $(m[u] + 1,\ c[u])$.
3. **Merge** each shifted child into the running $(m[v], c[v])$:
   - if $m[u] + 1 < m[v]$, replace the pair with $(m[u] + 1, c[u])$;
   - if $m[u] + 1 = m[v]$, add the counts;
   - if $m[u] + 1 > m[v]$, change nothing.

### 4. Counting pairs during the merge

Just **before** merging a shifted child, pair it with everything $v$ has accumulated so far ($v$
itself plus the children merged earlier):

- the candidate distance is $m[v] + m[u] + 1$;
- the number of pairs at that distance is $c[v] \cdot c[u]$.

Feed the candidate into a global $(\text{best}, \text{cnt})$: if the distance is smaller than
$\text{best}$, replace both; if it is equal, add to $\text{cnt}$. The starting value $(0, 1)$ for
a tower is exactly what handles shape 2 from section 1.

**Pairs with a later child are not lost.** A child is paired only with the children *before*
it, so the pairing between children $A$ and $C$ (with $A$ merged first) happens when $C$ is
merged, because $A$ is already in the running value by then:

| Step | The running $(m, c)$ already holds | Pairs counted in this step |
|---|---|---|
| merge $A$ | $v$ | $v$–$A$ |
| merge $B$ | $v$, $A$ | $v$–$B$, $A$–$B$ |
| merge $C$ | $v$, $A$, $B$ | $v$–$C$, $A$–$C$, $B$–$C$ |

When $C$ arrives, the running value only keeps the nearest towers among $v$, $A$ and $B$. If
$B$'s are closer than $A$'s, $A$'s towers have dropped out. That loses no minimum pair: the
$B$–$C$ pair would then be shorter than the $A$–$C$ pair, so $A$–$C$ was not at the minimum.
This is the lemma again.

**Candidates above the minimum are harmless.** A candidate at some node may be larger than the
global minimum. It simply loses to $\text{best}$, or is discarded when $\text{best}$ later
decreases and $\text{cnt}$ is reset.

### 5. Why no pair is counted twice

The term $c[v] \cdot c[u]$ counts pairs $(x, y)$ with $x$ in $v$'s running group and $y$ in $u$'s
subtree. Take a specific pair $\{a, b\}$:

1. **Only at one node, the LCA.** A step at $v$ only pairs towers on different branches of $v$.
   Above the LCA, $a$ and $b$ are in the same child subtree. At a node that is not an ancestor
   of both, at least one of them is not in its subtree at all.
2. **Only at one step at that node.** At the LCA, say $a$ is in branch $A$ (or $a = v$) and $b$
   is in branch $B$, with $B$ merged later. Merging $A$ happens before $B$ is there. Merging $B$
   counts the pair, because $A$ is already in the running group. No other step involves either
   tower.
3. **Never twice in the same term.** The two groups are disjoint, so the pair appears as $(x, y)$
   in only one way.

So each pair is counted **at most once**, and by the lemma each pair at the minimum distance is
counted **at least once**: exactly once.

### 6. Trace (sample 2)

Towers at 1, 4, 5, 6. Edges $2$–$1$, $4$–$2$, $1$–$3$, $6$–$3$, $2$–$5$. Rooted at 1:

```
        1*
       / \
      2   3
     / \   \
    4*  5*  6*
```

In the order the DFS performs the merges:

| At node | Merging child | Running $(m, c)$ before | Shifted child | Candidate | (best, cnt) | Running after |
|---|---|---|---|---|---|---|
| 2 | 4 | $(\infty, 0)$ | $(1, 1)$ | none | $(\infty, 0)$ | $(1, 1)$ |
| 2 | 5 | $(1, 1)$ | $(1, 1)$ | $2$, $1$ pair: $\{4,5\}$ | $(2, 1)$ | $(1, 2)$ |
| 1 | 2 | $(0, 1)$ | $(2, 2)$ | $2$, $2$ pairs: $\{1,4\}, \{1,5\}$ | $(2, 3)$ | $(0, 1)$ |
| 3 | 6 | $(\infty, 0)$ | $(1, 1)$ | none | $(2, 3)$ | $(1, 1)$ |
| 1 | 3 | $(0, 1)$ | $(2, 1)$ | $2$, $1$ pair: $\{1,6\}$ | $(2, 4)$ | $(0, 1)$ |

The answer is `2 4`, which matches the expected output.

### 7. Complexity

- **Time.** One DFS that looks at each edge a constant number of times: $O(N)$. On the largest
  inputs ($N = 2 \times 10^5$: stars, a long path, random trees) it runs in about 0.05 s.
- **Memory.** $O(N)$ for the adjacency lists and the arrays $m$, $c$.

---

## Implementation notes

- **64-bit counts.** $c$ and $\text{cnt}$ are `long long`. A star whose $199\,999$ leaves are all
  towers has $\binom{199\,999}{2} \approx 2 \times 10^{10}$ pairs at distance 2, which overflows
  a 32-bit `int`.
- **Recursion depth.** A path of $2 \times 10^5$ nodes makes the DFS that deep, which needs about
  20 MB of stack. MOJ gives 128 MB by default, so the recursive DFS is fine there. Locally it
  crashes with the default 8 MB stack on macOS / Linux (segmentation fault). Run `ulimit -s hard`
  in the terminal before testing. On judges with a small stack, the alternative is an iterative
  DFS: record a preorder with an explicit stack, then process it in reverse.
- **Infinity.** `INF = INT_MAX / 4`, so sums such as `m[v] + m[u] + 1` cannot overflow. In
  practice `m[v] + du` is only computed when both are finite.
- **Subtrees without towers** ($m[u] = \infty$) are skipped: they can neither form pairs nor
  change $v$'s value.
- **Input speed.** About $6 \times 10^5$ numbers are read, so `ios::sync_with_stdio(false)` and
  `cin.tie(0)` are used.
