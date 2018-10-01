#include <bits/stdc++.h>
using namespace std;

int shortest_repeating_cycle(string& seq) {
    // KMP : lps step
    int n = seq.size();
    int lps[n];
    lps[0] = 0;
    int i = 0, j = 1;
    while (j < n) {
        while (i > 0 and seq[i] != seq[j])
            i = lps[i-1];
        if (seq[i] == seq[j])
            lps[j] = ++i;
        else
            lps[j] = 0;
        j++;
    }
    int len = n - lps[n-1];
    return (n % len) ? n : len;
}

// test
int main() {
    string line; cin >> line;
    int cycle = shortest_repeating_cycle(line);
    cout << line.substr(0, cycle) << endl;
    return 0;
}