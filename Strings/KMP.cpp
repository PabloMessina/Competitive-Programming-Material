#include <bits/stdc++.h>
using namespace std;

// Build longest proper prefix/suffix array (lps) for pattern
// lps[i] = length of the longest prefix which is also suffix in substring pattern[0 .. i]
void preKMP(string& pattern, int lps[]) {
    int n = pattern.size();
    int j = 0; // j tracks the end of the current substring (and the char next to the previous suffix)
    int i = 0; // i tracks the char next to the previous prefix
    lps[0] = 0; // base case: no proper prefix/suffix for first substring (length 1)
    // An important invariant:
    //  at the beginning of every iteration of the main loop,
    //  pattern[0 .. i-1] = pattern[n-i .. n-1] = longest proper prefix/suffix of previous iteration (j-1)
    // We try to expand the previous prefix/suffix pair, but when a mismatch between i and j happens
    // we set i next to the end of the second (and third, fourth, ... ) longest proper prefix
    // until a match is found or we run out of prefixes
    while (j < n) {
        while (i > 0 && pattern[i] != pattern[j]) // find longest proper prefix/suffix
            i = lps[i-1]; // try next longest prefix (we reuse previous knowledge)
        if (pattern[i] == pattern[j]) // match found
            lps[j] = ++i;
        else // no match found
            lps[j] = 0;
        j++;
    }
}

// Count number of matches of pattern string in target string using KMP algorithm
int KMP(string& pattern, string& target) {
    int n = pattern.size(), m = target.size();
    int lps[n];
    preKMP(pattern, lps); // build lps array
    int matches = 0;
    int i = 0; // i tracks current char in pattern to compare
    int j = 0; // j tracks current char in target to compare
    // Invariant:
    //  at the beginning of each iteration of the main loop,
    //  pattern[0 .. i-1] = target[j-i .. j-1]
    // We try to expand the previous match one more char, but in case of mistmatch between i and j,
    // we 'shift' the pattern to to right by setting i next to the end of the lps of the previous match,
    // and so on, until a match is found or we run out of prefixes.
    while (j < m) {
        while (i > 0 && pattern[i] != target[j]) // try to keep prefix before i as long as possible while ensuring i matches j
            i = lps[i-1];
        if (pattern[i] == target[j]) { // if i did match j
            i++; // keep invariant for next iteration
            if (i == n) { // we matched the whole pattern
                i = lps[i-1]; // shift the pattern so that the longest proper prefix/suffix pair is aligned
                matches++; // increase count
            }
        }
        j++; // keep invariant for next iteration
    }
    return matches;
}

int main() {
    string target, pattern;
    while (true) {
        getline(cin, target);
        getline(cin, pattern);
        printf("%d matches\n", KMP(pattern, target));
    }
    return 0;
}