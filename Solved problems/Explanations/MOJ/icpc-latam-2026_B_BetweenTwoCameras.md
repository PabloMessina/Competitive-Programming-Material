# B. Between Two Cameras

- Problem: [MOJ, icpc-latam-2026 B](https://moj.naquadah.com.br/treino/problema/?id=icpc-latam-2026%23b-cats) (ICPC Latin America 2026 collection)
- Solution: [`icpc-latam-2026_B_BetweenTwoCameras.cpp`](../../MOJ/icpc-latam-2026_B_BetweenTwoCameras.cpp) (Fenwick tree)
- Alternative: [`icpc-latam-2026_B_BetweenTwoCameras_v2.cpp`](../../MOJ/icpc-latam-2026_B_BetweenTwoCameras_v2.cpp) (segment tree)

**Problem.** $N$ cats sit at integer points $(X, Y)$ with $1 \le X \le D - 1$ and $Y \ge 1$, each
with a weight $W$. Two cameras at $(0, 0)$ and $(D, 0)$ each start pointing at the other camera
and turn $90^\circ$ into the room, listing the cats in the order they see them. A pair of cats is
*flagged* if the two lists order it differently, and costs the product of the two weights. Output
the total cost of the flagged pairs. Limits: $2 \le N \le 2 \times 10^5$,
$2 \le D \le 10^9$, $Y \le 10^9$, $W \le 10^4$, time limit 2 s. No camera ever sees two cats at
once.

**Tags.** geometry, polar sort, cross product, counting inversions, fenwick tree.

---

## Summary: the key points

1. **Each camera's list is a polar sort.**
   - Camera 1 sorts the vectors $(X, Y)$ counter-clockwise from the $+x$ axis.
   - Camera 2 turns clockwise, but mirroring the room ($X \to D - X$) makes it the same as
     camera 1: it sorts the vectors $(D - X, Y)$ counter-clockwise.

2. **Sort with integers only.**
   - The cross product decides which of two vectors comes first. With coordinates up to $10^9$ it
     is at most $10^{18}$, which fits in a `long long`, so the sort is exact.
   - With `double` it is not: cross products of about $10^{18}$ lose their last digits, and cats
     that are almost on the same ray get sorted wrong.

3. **Flagged pairs are inversions between the two lists.**
   - Walk list 1 from the end and insert each cat's weight into a Fenwick tree at its position in
     list 2.
   - When cat $i$ is reached, the tree holds the cats after $i$ in list 1. Those at positions
     below $i$'s in list 2 are before $i$ there, so they form flagged pairs with $i$:
     add $W_i$ times their total weight.

4. **Use 64-bit numbers.** Weight sums reach $2 \times 10^9$ and the answer reaches about
   $2 \times 10^{18}$. $O(N \log N)$ in total.

---

## In depth

### 1. Each camera's list is a polar sort

**Camera 1** is at the origin. It starts pointing at $(D, 0)$, along the $+x$ axis, and turns
$90^\circ$ toward $Y > 0$: counter-clockwise. It sees a cat when the angle of the vector $(X, Y)$
is reached, so list 1 is the cats sorted by that angle, counter-clockwise.

**Camera 2** is at $(D, 0)$. It starts pointing at the origin, along the $-x$ axis, and turns
toward $Y > 0$: clockwise. Reflect the room in the vertical line $x = D/2$, which maps $X$ to
$D - X$. Camera 2 lands at the origin, it now starts along $+x$, and the clockwise turn becomes
counter-clockwise. So list 2 is the vectors $(D - X, Y)$ sorted counter-clockwise, exactly like
camera 1.

All vectors have positive coordinates (both $X \ge 1$ and $D - X \ge 1$), so they all lie
strictly inside the first quadrant.

### 2. Sorting with integers only

For two vectors $a$ and $b$ in the same quadrant, $a$ comes first counter-clockwise exactly when
$b$ is to its left:

$$a \times b = a_x b_y - a_y b_x > 0.$$

That's the comparison in `Point2D`'s `operator<`. Vectors in different quadrants are ordered by
quadrant, and inside one quadrant, which spans less than $180^\circ$, the cross product decides.
Here everything is in quadrant 0, so only the cross product matters.

**Why `long long` and not `double`.** Each product $a_x b_y$ is up to
$10^9 \cdot 10^9 = 10^{18}$, which is below $9.2 \times 10^{18}$, so with integers the
comparison is exact. A `double` stores integers exactly only up to $2^{53} \approx 9 \times 10^{15}$,
so each product is rounded by up to about 100. Two cats almost on the same ray, with
coordinates around $10^9$, can have a cross product of exactly $\pm 1$, and the rounding then
gets the sign wrong about half the time. Random tests don't catch this, because random cats
have large cross products. On 40 adversarial tests full of such pairs (300 cats each), the
`double` version gave the wrong answer on **all 40**, and the `long long` version was right on
all 40.

The statement guarantees that a camera never sees two cats at once, so no two vectors have the
same angle and the sort has no ties.

### 3. Flagged pairs are inversions

Let $\text{pos}_2[c]$ be the position of cat $c$ in list 2. A pair is flagged when the two lists
disagree on its order. That is an **inversion** between the two lists: if $k$ comes after $i$
in list 1, then

$$\{i, k\} \text{ is flagged} \iff \text{pos}_2[k] < \text{pos}_2[i].$$

The answer is the **weighted inversion count**: the sum of $W_i \cdot W_k$ over all inversions.

**Counting with a Fenwick tree.** Walk list 1 from the **last** cat to the first. For each cat
$i$:

1. **Query.** The tree holds the cats after $i$ in list 1, each at its list-2 position. The ones
   at positions $1 \ldots \text{pos}_2[i] - 1$ come before $i$ in list 2, so each forms a flagged
   pair with $i$:
   $$\text{answer} \mathrel{+}= W_i \cdot \text{sum}\big(1,\ \text{pos}_2[i] - 1\big).$$
2. **Insert.** Add $W_i$ at position $\text{pos}_2[i]$.

$W_i$ factors out of the sum because every pair contributes $W_i \cdot W_k$.

**No pair is missed or counted twice.** Take a flagged pair $\{i, k\}$ with $i$ before $k$ in
list 1. Because the walk goes backwards, $k$ is inserted first. When $i$ is reached, $k$ is in
the tree at a position below $\text{pos}_2[i]$, so the pair is counted. It's counted only at
$i$: when $k$ was processed, $i$ was not in the tree yet.

### 4. Trace (sample 2)

$D = 10$, all three cats at height 3. Cat 1 is at $X = 5$ ($W = 2$), cat 2 at $X = 8$
($W = 3$), cat 3 at $X = 2$ ($W = 1$).

| Cat | Camera 1: $(X, Y)$ | slope $Y/X$ | Camera 2: $(D - X, Y)$ | slope $Y/(D - X)$ |
|---|---|---|---|---|
| 1 | $(5, 3)$ | 0.6 | $(5, 3)$ | 0.6 |
| 2 | $(8, 3)$ | 0.375 | $(2, 3)$ | 1.5 |
| 3 | $(2, 3)$ | 1.5 | $(8, 3)$ | 0.375 |

A smaller slope means a smaller angle, so list 1 $= [2, 1, 3]$ and list 2 $= [3, 1, 2]$, which
gives $\text{pos}_2 = \{3 \mapsto 1,\ 1 \mapsto 2,\ 2 \mapsto 3\}$. Walking list 1 backwards:

| Cat | $\text{pos}_2$ | sum of positions $1 \ldots \text{pos}_2 - 1$ | added to the answer | answer |
|---|---|---|---|---|
| 3 | 1 | 0 (empty) | $1 \cdot 0 = 0$ | 0 |
| 1 | 2 | 1 (cat 3) | $2 \cdot 1 = 2$ | 2 |
| 2 | 3 | 3 (cats 3 and 1) | $3 \cdot 3 = 9$ | 11 |

The answer is 11, which matches the expected output. The two lists are exact reverses of each
other, so every pair is flagged: $2 \cdot 3 + 2 \cdot 1 + 3 \cdot 1 = 11$.

### 5. Complexity

- **Time.** Two sorts with an $O(1)$ comparator and $N$ Fenwick queries and updates:
  $O(N \log N)$. On the largest inputs ($N = 2 \times 10^5$, coordinates up to $10^9$) it runs in
  about 0.05 s.
- **Memory.** $O(N)$.

---

## Implementation notes

- **Library code.** The solution pastes trimmed copies of two library files:
  - `Geometry/2D/Point2D.cpp`, keeping only the cross product, `quad()` and `operator<`, with
    `typedef long long T` instead of `double`.
  - `Data_Structures/fenwick_tree.cpp`, templated on the value type so it can be used as
    `FT<ll>`.
- **Segment tree alternative (v2).** The v2 solution is the same algorithm with the iterative
  segment tree from `Data_Structures/segment_tree.cpp` and a range-sum node `rsumq`. Its positions
  are 0-indexed and its queries are half-open, so the cats before $i$ in list 2 are
  `query(0, pos2[i])`. It uses `set_point` instead of adding, which works because each position
  starts empty and is set exactly once. A Fenwick tree is shorter and is all this problem needs.
  A segment tree is more general: changing the node struct gives min, max, or any other
  associative operation.
- **64-bit everywhere.** A Fenwick sum reaches $2 \times 10^5 \cdot 10^4 = 2 \times 10^9$, more
  than an `int` holds. The answer is at most the sum over all pairs,
  $\approx (2 \times 10^9)^2 / 2 = 2 \times 10^{18}$. The extreme case (every pair flagged, all
  weights $10^4$) gives exactly $1\,999\,990\,000\,000\,000\,000$, which fits in a `long long`.
- **1-indexed positions.** The Fenwick tree uses positions $1 \ldots N$, so `pos2` stores
  positions in list 2 plus one, and `query(pos2[i] - 1)` is the sum of the cats strictly before
  $i$. `query(0)` returns 0.
- **Mirroring** camera 2 means the same `operator<` sorts both lists. Without it, sorting the
  vectors $(X - D, Y)$ counter-clockwise would give list 2 reversed.
