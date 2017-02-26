#include <bits/stdc++.h>
using namespace std;

void shortest_repeating_cycle(string& s) {
    int n = s.size();

    // KMP : lps step
    int lps[n];
    lps[0] = 0;
    int i = 0, j = 1;
    while (j < n) {
        while (i > 0 && s[i] != s[j])
            i = lps[i-1];
        if (s[i] == s[j])
            lps[j] = ++i;
        else
            lps[j] = 0;
        j++;
    }

    // print smallest repeating cycle
    int len = n - lps[n-1];
    if (len != n and (n % len == 0))
        printf("%.*s\n", len, s.c_str());
    else
        puts(s.c_str());
}


int main() {
    while (true) {
        string input; getline(cin, input); 
        shortest_repeating_cycle(input);
    }
    return 0;
}