# Tests

Tests for the reusable templates in this repo (`Data_Structures/`, `Mathematics/`, etc.).
Solved problems don't need tests here.

This folder is not part of the notebook PDF: `make.py` only includes the folders
listed under `sections` in `config.yaml`.

## Running a test

From the repo root:

```bash
g++-15 -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG Tests/test_segment_tree_lazy.cpp -o test.out && ./test.out
```

Use `g++-15` (Homebrew GCC), not `g++`: on macOS, `g++` is Apple clang, which
defaults to C++14 and has no `bits/stdc++.h`.

Flags:

- `-std=c++17`: the templates may use C++17 features.
- `-Wall -Wextra`: warnings often point to real bugs (unused variables, sign comparisons, ...).
- `-D_GLIBCXX_DEBUG`: makes `vector`, `string`, etc. check bounds and crash immediately on
  out-of-range access, instead of silently reading garbage. (`-fsanitize=address` would be
  better, but Homebrew GCC on macOS can't link it.)

A test prints `OK` lines and exits with code 0 when everything passes. If an `assert`
fails, it prints the file, line and failed condition, and aborts.

To run every test:

```bash
for f in Tests/test_*.cpp; do
    echo "== $f"
    g++-15 -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG "$f" -o test.out && ./test.out || echo "FAILED: $f"
done
```

`*.out` is in `.gitignore`, so the compiled binary won't be committed.

## Writing a new test

Name it `Tests/test_<template_name>.cpp`. The pattern is a **randomized comparison against
a brute force**:

1. **Include the template.** Template files are snippets: they rely on the usual header,
   `using namespace std;` and typedefs like `ll`, so define those first. If the template
   has its own `main()` with examples, rename it while including:

   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   typedef long long ll;
   #define main example_main
   #include "../Data_Structures/my_template.cpp"
   #undef main
   ```

2. **Write a brute force** that is obviously correct, usually a few loops over a `vector`.

3. **Generate random operations** with a fixed seed (so failures are reproducible), apply
   them to both, and `assert` the results match:

   ```cpp
   mt19937 rng(12345);
   int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

   for (int iter = 0; iter < 300; iter++) {
       int n = rnd(1, 40);
       // build both structures, then run ~200 random operations comparing them
   }
   ```

Tips:

- **Keep sizes small** (n up to ~40) and run many iterations. Small sizes hit edge cases
  much more often: n = 1, empty ranges, ranges touching the ends, sizes that aren't powers
  of 2.
- **Keep values small** too, so that collisions/ties happen (equal elements, zero sums...).
- **Test every public function**, including the less common ones.
- **Check the template's own examples** by calling `example_main()` at the end.
- **When an assert fails**, shrink `n` and the number of operations until the failing case
  is small enough to trace by hand, then print the operations.
