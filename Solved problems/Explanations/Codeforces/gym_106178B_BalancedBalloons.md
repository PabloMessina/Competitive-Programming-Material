# B. Balanced Balloons

- Problem: [Codeforces Gym 106178 B](https://codeforces.com/gym/106178/problem/B) (2025-2026 ICPC Latin American Regional Programming Contest)
- Solution: [`gym_106178B_BalancedBalloons.cpp`](../../Codeforces/gym_106178B_BalancedBalloons.cpp)
- Statements: [contest PDF](https://scorelatam.naquadah.com.br/latam-2025/contest.pdf)

**Problem.** $N$ people join a club one by one, and each brings between 1 and $K$ balloons. After
each person joins, the total number of balloons so far must be divisible by the number of people
so far. Count the sequences of $N$ contributions that satisfy this at every step, modulo
$998244353$. Limits: $1 \le N \le 10^9$, $1 \le K \le 2000$.

**Tags.** dp, top-down, memoization, counting, math, harmonic sum.

---

## Summary: the key points

1. **Track the average, not the total.**
   - After $i$ people the total $T_i$ is divisible by $i$, so the average $a_i = T_i / i$ is an
     integer, and $T_i = i \cdot a_i$.
   - The average of numbers in $[1, K]$ is in $[1, K]$, so it has at most $K$ values.

2. **Choosing the next contribution is choosing the next average.**
   - $x = (i+1)\,a' - i\,a$, so each contribution $x$ matches exactly one new average $a'$.
   - $1 \le x \le K$ becomes
     $\lceil (ia + 1)/(i+1) \rceil \le a' \le \lfloor (ia + K)/(i+1) \rfloor$.
   - The range always contains $a' = a$ (bring $x = a$).

3. **The range shrinks, so after about $K$ people everything is forced.**
   - The range has real length $(K - 1)/(i + 1)$.
   - Once $i + 1 > K - 1$, only $a' = a$ fits, so $N$ can be capped at about $K$.
   - If the range is a single value at some step, it stays a single value forever.

4. **Memoized DP over (people so far, average).**
   - $dp(i, a) = \sum_{a'} dp(i + 1, a')$, starting from $dp(0, 0)$.
   - About $K^2$ states, and the loops add up to a harmonic sum: $\approx K^2 \ln K$ operations.

---

## In depth

### 1. Track the average, not the total

The rule says that after $i$ people, the total $T_i$ is divisible by $i$. So

$$a_i = \frac{T_i}{i}$$

is an integer, and the total can be recovered as $T_i = i \cdot a_i$. Every contribution is
between 1 and $K$, so the average is too. The total can reach about $2 \cdot 10^{12}$, but the
average only needs $K \le 2000$ values. This is what makes a DP possible.

### 2. Choosing the next contribution is choosing the next average

Person $i + 1$ brings $x$ balloons, and the new average must be an integer:

$$a' = \frac{i \cdot a + x}{i + 1} \quad\Longleftrightarrow\quad x = (i + 1)\,a' - i\,a.$$

Each valid $x$ gives exactly one integer $a'$, and each integer $a'$ gives exactly one $x$. So
counting contribution sequences is the same as counting **sequences of averages**. Substituting
into $1 \le x \le K$:

$$\left\lceil \frac{i\,a + 1}{i + 1} \right\rceil \;\le\; a' \;\le\; \left\lfloor \frac{i\,a + K}{i + 1} \right\rfloor.$$

These are `a_min` and `a_max` in the code. The range is never empty: $a' = a$ corresponds to
$x = a \in [1, K]$.

*Example* ($K = 3$, $i = 1$, $a = 3$): $a' \in [\lceil 4/2 \rceil, \lfloor 6/2 \rfloor] = [2, 3]$.
$a' = 2$ means $x = 2 \cdot 2 - 3 = 1$, and $a' = 3$ means $x = 3$.

### 3. The range shrinks, so after about $K$ people everything is forced

Before rounding, the interval has length

$$\frac{(i\,a + K) - (i\,a + 1)}{i + 1} = \frac{K - 1}{i + 1},$$

which decreases as people join. Once $i + 1 > K - 1$, the length is below 1, so the interval
holds at most one integer. Since $a$ is always in it, that integer is $a$: every later person
must bring exactly $a$ balloons, and there is exactly one way to finish.

**Capping $N$.** The code uses `actual_N = min(N, 2002)` and returns 1 when $i$ reaches it. By then
$i + 1 > K - 1$ for every $K \le 2000$, so the remaining steps are forced. This is what handles
$N$ up to $10^9$.

**Early return when the range is a single value.** Write the range relative to the current
average:

$$a' \in a + \left[\frac{1 - a}{i + 1},\ \frac{K - a}{i + 1}\right].$$

The left offset is $\le 0$ and the right offset is $\ge 0$. If the average stays $a$, the next
step divides the same offsets by $i + 2$ instead of $i + 1$, so both ends move toward $a$ and the
next interval lies inside the current one. If only $a$ fits now, only $a$ fits at every later
step, so the code can return 1 immediately. That's the `a_min == a_max` check.

### 4. The DP

- **State.** $dp(i, a)$ is the number of ways to finish when $i$ people have joined and the
  average is $a$.
- **Start.** The answer is $dp(0, 0)$. The 0 is a convention: $i \cdot a = 0$ either way, so the
  first range is $[1, K]$.
- **Transition.**
  $$dp(i, a) = \sum_{a' = a_{\min}}^{a_{\max}} dp(i + 1, a') \pmod{998244353}.$$
- **Base cases.** $dp(i, a) = 1$ when $i$ reaches `actual_N`, and $dp(i, a) = 1$ when
  $a_{\min} = a_{\max}$.

*Trace* (sample 1: $N = K = 3$):

| State | Range for $a'$ | Result |
|---|---|---|
| $i = 0,\ a = 0$ | $[1, 3]$ | $2 + 1 + 2 = 5$ |
| $i = 1,\ a = 1$ | $[\lceil 2/2 \rceil, \lfloor 4/2 \rfloor] = [1, 2]$ | both continuations are forced: $[1,1,1]$, $[1,3,2]$, so 2 |
| $i = 1,\ a = 2$ | $[\lceil 3/2 \rceil, \lfloor 5/2 \rfloor] = [2, 2]$ | single value: $[2,2,2]$, so 1 |
| $i = 1,\ a = 3$ | $[\lceil 4/2 \rceil, \lfloor 6/2 \rfloor] = [2, 3]$ | both continuations are forced: $[3,1,2]$, $[3,3,3]$, so 2 |

The answer is 5, which matches the expected output.

### 5. Complexity

- **States.** At most about $K$ useful steps times $K$ averages, about $2000 \times 2000$. The
  `long long` memo table takes about 32 MB, well within the 1024 MB limit.
- **Time.** A state at step $i$ loops over about $(K - 1)/(i + 1) + 1$ values, so the total is a
  harmonic sum:
  $$\sum_{i} K \left( \frac{K}{i + 1} + 1 \right) \approx K^2 \ln K + K^2 \approx 3 \cdot 10^7.$$

---

## Implementation notes

- The ceiling is computed with integer arithmetic as `(aux + i) / (i+1)`, with `aux = a * i + 1`.
  This is the identity $\lceil x / b \rceil = \lfloor (x + b - 1) / b \rfloor$ for $x \ge 0$,
  $b > 0$. Avoid `-(-x / b)` in C++: division truncates toward zero, so it does not give the
  ceiling. All values stay below $2001 \cdot 2002 + 2000$, so `int` is enough.
- `assert(a_min <= a_max)` documents that $a' = a$ is always in range.
- The memo is initialized to $-1$ with `memset`, which works because every byte of $-1$ is
  `0xFF`.
