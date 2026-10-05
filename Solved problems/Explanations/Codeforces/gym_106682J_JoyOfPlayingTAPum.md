# J. Joy of playing TAPum

- Problem: [Codeforces Gym 106682 J](https://codeforces.com/gym/106682/problem/J) (2026 Argentinian Programming Tournament, TAP)
- Solution: [`gym_106682J_JoyOfPlayingTAPum.cpp`](../../Codeforces/gym_106682J_JoyOfPlayingTAPum.cpp)

**Problem.** A string of length $N \le 999$ has equally many `T`, `A` and `P`. A move deletes three
**adjacent**, pairwise different characters (the rest closes the gap). Can the whole string be
deleted?

**Tags.** interval DP, top-down DP with memoization, non-crossing partitions, CYK / grammar
binarization.

---

## Summary: the key points

1. **Characterizing "impossible" is a dead end; think about which characters go together.**
   - Some losing strings still have moves available (e.g. `TPPAPATAT`), and losing strings don't
     follow a simple pattern.
   - Instead, look at which **original positions** $i < k < m$ are deleted together in each move.

2. **The triples never interleave.**
   - When $i, k, m$ are deleted they are adjacent, so everything originally between them was
     already gone.
   - So two triples are either nested or side by side: they form a forest, and moves in different
     branches don't interfere.

3. **The game is won iff the string splits into non-crossing triples of distinct letters.**
   - The order of moves doesn't matter, as long as inner parts go first.
   - This is a property of segments of the original string, so: interval DP.

4. **Recurrence: look at the triple containing the leftmost character.**
   - If $s_l$ is deleted with $s_k$ and $s_m$, the segment splits into three independent pieces.
   - Trying every $(k, m)$ for every segment is $O(N^4)$: too slow.

5. **Add an auxiliary state to choose $k$ and $m$ in separate steps.**
   - `closed(l, m)`: $s[l..m]$ can be erased with $s_l$ and $s_m$ in the same triple.
   - Each function then loops over one index: $O(N^3)$. This is grammar binarization, as in CYK.

6. **Only lengths that are multiples of 3 matter.**
   - Indices move in steps of 3, leaving about $N^3 / 54 \approx 2 \times 10^7$ checks.

---

## In depth

### 1. Characterizing "impossible" is a dead end

A natural first idea is to describe when no win is possible: for example, "there is no triple of
adjacent different letters". That's sufficient but far from necessary. A brute force over all
small strings shows:

- there are losing strings that still have moves, the smallest of length 9, e.g. `TPPAPATAT`;
- they don't follow an obvious pattern.

Backtracking over move sequences is exponential. We need a different angle.

### 2. The triples never interleave

Label the characters by their **original** positions. Each move deletes three characters at
original positions $i < k < m$. At the moment of the move they are adjacent, so every character
originally strictly between $i$ and $k$, or between $k$ and $m$, was deleted earlier.

Take two triples $(i_1, k_1, m_1)$ and $(i_2, k_2, m_2)$. They can't interleave, e.g.
$i_1 < i_2 < k_1 < k_2$: the first triple needs $i_2$ gone before it is deleted, and the second
needs $k_1$ gone before it is deleted, which is circular. So any two triples are either:

- **side by side**: one lies entirely before the other; or
- **nested**: one lies entirely inside a gap of the other.

The triples form a forest. Each triple's two gaps contain whole subtrees that must be erased first,
and different branches are independent.

### 3. The game is won iff the string splits into non-crossing triples of distinct letters

The converse also holds: given any partition into non-crossing triples of pairwise different
letters, delete them innermost first (children before parents). Each triple's gaps are already
empty when its turn comes, so its three characters are adjacent and the move is legal.

So the order of the moves is irrelevant. The question is purely structural: **does the original
string have a non-crossing partition into triples of three different letters?** That depends only
on segments of the original string, which suggests an interval DP.

*Example* (first sample, `AAPTTAPPT`, positions 0 to 8): the moves in the statement delete the
triples $(4, 5, 6)$ = `TAP`, then $(1, 2, 3)$ = `APT`, then $(0, 7, 8)$ = `APT`. The last triple
has a gap $1..6$ containing the other two triples side by side.

### 4. Recurrence: look at the triple containing the leftmost character

Let $\mathrm{can}(l, r)$ mean "$s[l..r]$ can be completely erased on its own" (segments inclusive;
an empty segment is erasable). Character $s_l$ is deleted together with some $s_k$ and $s_m$,
where $l < k < m \le r$ and the three letters are different. Then three pieces must be erasable
independently:

- $s[l+1..k-1]$, nested in the first gap of the triple;
- $s[k+1..m-1]$, nested in the second gap;
- $s[m+1..r]$, to the right of the triple.

$$\mathrm{can}(l, r) = \bigvee_{l < k < m \le r} \Big( \lbrace s_l, s_k, s_m\rbrace \text{ distinct} \wedge \mathrm{can}(l{+}1, k{-}1) \wedge \mathrm{can}(k{+}1, m{-}1) \wedge \mathrm{can}(m{+}1, r) \Big)$$

There are $O(N^2)$ segments and $O(N^2)$ pairs $(k, m)$ each: $O(N^4)$, too slow for $N = 999$.

### 5. Add an auxiliary state to choose $k$ and $m$ in separate steps

The first three conditions only involve $l$, $k$ and $m$, not $r$: they describe the part covered
by $s_l$'s triple. Store that part in its own function:

$$\mathrm{closed}(l, m) = \bigvee_{l < k < m} \Big( \lbrace s_l, s_k, s_m\rbrace \text{ distinct} \wedge \mathrm{can}(l{+}1, k{-}1) \wedge \mathrm{can}(k{+}1, m{-}1) \Big)$$

meaning "$s[l..m]$ can be erased with $s_l$ and $s_m$ in the same triple". The main recurrence then
only chooses where $s_l$'s triple ends:

$$\mathrm{can}(l, r) = \bigvee_{l < m \le r} \Big( \mathrm{closed}(l, m) \wedge \mathrm{can}(m{+}1, r) \Big)$$

Each function loops over a single index, so the total is $O(N^3)$.

**This is a standard technique.** Erasable strings form a context-free language:

$$S \to \varepsilon \mid x\ S\ y\ S\ z\ S \qquad (x, y, z \text{ pairwise different letters})$$

The CYK algorithm decides membership with an interval DP, and it is $O(n^3)$ when every rule has at
most two parts with a free split point between them. Long rules are rewritten with helper symbols
("binarization"). Here the helper symbol $C$ is exactly `closed`:

$$S \to \varepsilon \mid C\ S, \qquad C \to x\ S\ y\ S\ z.$$

$C$'s rule still has several parts, but $x$ and $z$ are fixed at the segment's ends, so only one
split point ($k$) is free. In competitive programming the same trick is usually described as
"adding an auxiliary state" to split a transition that chooses several things at once.

### 6. Only lengths that are multiples of 3 matter

Every erasable segment has length divisible by 3. So:

- $\mathrm{can}(l, r)$ is false unless $(r - l + 1) \bmod 3 = 0$;
- $m$ only takes values with $(m - l + 1) \bmod 3 = 0$: steps of 3;
- $k$ only takes values with $(k - l - 1) \bmod 3 = 0$, i.e. $k = l + 1, l + 4, \ldots$; then the
  second gap automatically has a valid length too.

That leaves roughly $N^3 / 54 \approx 2 \times 10^7$ checks per function for $N = 999$. In
practice the solution runs in about 0.1 s.

### Implementation notes

The solution is top-down, which mirrors the recurrences directly:

```cpp
bool can(int l, int r) {
    if (l > r) return true;                  // empty segment
    if ((r - l + 1) % 3 != 0) return false;
    signed char& ans = memo_can[l][r];
    if (ans != -1) return ans;
    for (int m = l + 2; m <= r; m += 3)
        if (closed(l, m) && can(m + 1, r)) return (ans = 1);
    return (ans = 0);
}

bool closed(int l, int m) {
    signed char& ans = memo_closed[l][m];
    if (ans != -1) return ans;
    for (int k = l + 1; k < m; k += 3)
        if (s[l] != s[k] && s[k] != s[m] && s[l] != s[m]
            && can(l + 1, k - 1) && can(k + 1, m - 1)) return (ans = 1);
    return (ans = 0);
}
```

- Memo tables are `signed char` with $-1$ meaning "not computed": $2 \times 1000^2$ bytes = 2 MB.
- Recursion depth is $O(N)$, about 1000 calls: no stack issues.
- Each function returns as soon as it finds a way to erase the segment.

**Side fact.** The game is invariant under rotating the string (moving the first character to the
end). That follows from the structure: a non-crossing partition of a string is also non-crossing
when the string is read as a circle.
