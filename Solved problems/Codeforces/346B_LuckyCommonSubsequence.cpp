// tags: DP, longest common subsequence, KMP, strings
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef tuple<int,int,int> iii;
// -------------------------------
string s1, s2, virus;
int n1, n2, nv;
int lps[100];
int memo_lcs[100][100][100]; // remember solutions
iii memo_next[100][100][100]; // remember next subproblem in optimal solution
// dp(i,j,k) = length of the longest common subsequence between s1[i .. n1-1] and s2[j .. n2-1]
// such that it doesn't contain virus[k .. nv-1] as a substring
// Notice dp(0,0,0) is the solution to the original problem
int dp(int i, int j, int k) {
    // bases cases
    if (k == nv) return -1;
    if (i == n1 or j == n2) return 0;
    // already solved
    int& ans = memo_lcs[i][j][k];
    if (ans != -1) return ans;
    
    int tmp;
    iii& nxt = memo_next[i][j][k];
    // option 1
    if (s1[i] == s2[j]) {
        int kk = k;
        while (virus[kk] != s1[i] and kk > 0) kk = lps[kk-1];
        if (virus[kk] == s1[i]) kk++;
        tmp = dp(i+1, j+1, kk);
        if (tmp != -1 and tmp + 1 > ans) { ans = tmp + 1; nxt = iii(i+1, j+1, kk); }
    }
    // option 2
    tmp = dp(i+1, j, k);
    if (tmp != -1 and tmp > ans) { ans = tmp; nxt = iii(i+1, j, k); }
    // option 3
    tmp = dp(i, j+1, k);
    if (tmp != -1 and tmp > ans) { ans = tmp; nxt = iii(i, j+1, k); }
    return ans;
}

init_lps() {
    lps[0] = 0;
    rep(j,1,nv-1) {
        int i = lps[j-1];
        while (virus[i] != virus[j] and i > 0) i = lps[i-1];
        lps[j] = virus[i] == virus[j] ? i+1 : 0;
    }
}

int main() {
    cin >> s1 >> s2 >> virus;
    n1 = s1.size();
    n2 = s2.size();
    nv = virus.size();
    memset(memo_lcs, -1, sizeof memo_lcs);
    init_lps();
    int lcs = dp(0,0,0);
    if (lcs == 0) cout << "0\n";
    else {
        int i = 0, j = 0, k = 0;
        while (i < n1 and j < n2) {
            auto& nxt = memo_next[i][j][k];
            int ii = get<0>(nxt);
            int jj = get<1>(nxt);
            int kk = get<2>(nxt);
            if (ii > i and jj > j) cout << s1[i];
            i = ii; j = jj; k = kk;
        }
        cout << '\n';
    }
    return 0;
}