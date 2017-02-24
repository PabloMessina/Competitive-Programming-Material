// tags: KMP modified
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=a; i<=b; ++i)

const int MAXN = 500000;
int lastIndex[26];
int target[MAXN];
int pattern[MAXN];
int lps[MAXN];
int n, m;

int main() {

    // --- build target ---
    string input;
    getline(cin, input);
    m = input.size();

    memset(lastIndex, -1, sizeof(lastIndex));
    rep(i,0,m-1) {
        int c = input[i] - 'a';
        target[i] = (lastIndex[c] == -1 ? 0 : i - lastIndex[c]);
        lastIndex[c] = i;
    }

    // --- build pattern ---
    scanf("%d", &n);

    memset(lastIndex, -1, sizeof(lastIndex));
    rep(i,0,n-1) {
        int k; scanf("%d", &k); --k;
        pattern[i] = (lastIndex[k] == -1 ? 0 : i - lastIndex[k]);
        lastIndex[k] = i;
    }

    // ---- KMP modified ----

    int i, j, c;

    // 1.- build longest proper prefix-suffix array    
    i = 0, j = 1;
    while (j < n) {
        while (true) {
            c = (i - pattern[j] >= 0 ? pattern[j] : 0);
            if (i == 0 or pattern[i] == c) break;
            i = lps[i-1];
        }        
        if (pattern[i] == c)
            lps[j] = ++i;
        else
            lps[j] = 0;
        j++;
    }

    // 2.- count pattern matches
    i = j = 0;
    int matches = 0;
    while (j < m) {
        while (true) {
            c = (i - target[j] >= 0 ? target[j] : 0);
            if (i == 0 or pattern[i] == c) break;
            i = lps[i-1];
        }
        if (pattern[i] == c) {
            i++;
            if (i == n) {
                matches++;
                i = lps[i-1];
            }
        }
        j++;
    }

    // --- print output ---
    printf("%d\n", matches);
    return 0;
}