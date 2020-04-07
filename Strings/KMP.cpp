#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; ++i)

// Build longest proper prefix/suffix array (lps) for pattern
// lps[i] = length of the longest proper prefix which is also suffix in pattern[0 .. i]
void init_lps(string& pattern, int lps[]) {
    int n = pattern.size();
    lps[0] = 0; // base case: no proper prefix/suffix for pattern[0 .. 0] (length 1)
    rep(j, 1, n) { // for each pattern[0 .. j]
        int i = lps[j-1]; // i points to the char next to lps of previous iteration
        while (pattern[i] != pattern[j] and i > 0) i = lps[i-1];
        lps[j] = pattern[i] == pattern[j] ? i+1 : 0;
    }
}

// Count number of matches of pattern string in target string using KMP algorithm
int count_matches(string& pattern, string& target) {
    int n = pattern.size(), m = target.size();
    int lps[n];
    init_lps(pattern, lps); // build lps array
    int matches = 0;
    int i = 0; // i tracks current char in pattern to compare
    rep(j, 0, m) { // j tracks each char in target to compare
        // try to keep prefix before i as long as possible while ensuring i matches j        
        while (pattern[i] != target[j] and i > 0) i = lps[i-1];
        if (pattern[i] == target[j]) {
            if (++i == n) { // we matched the whole pattern
                i = lps[n-1]; // shift the pattern so that the longest proper prefix/suffix pair is aligned
                matches++;
            }
        }
    }
    return matches;
}

int main() { // usage
    string target, pattern;
    while (true) {
        cin >> target >> pattern;
        cout << count_matches(pattern, target) << " matches\n";
    }
    return 0;
}