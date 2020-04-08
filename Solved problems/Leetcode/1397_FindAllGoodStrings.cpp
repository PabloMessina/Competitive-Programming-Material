// tags: DP, strings, KMP, implementation
#include <bits/stdc++.h>
using namespace std;

class Solution {
    #define rep(i,a,b) for(int i = a; i < b; ++i)
    #define invrep(i,b,a) for(int i = b; i >= a; --i)
    typedef long long int ll;
    
public:
    
    const static ll MOD = 1000000007;
    ll memo[500][50][2];
    int lps[50];
    string word, evil;
    int n, m;
    
    bool find_predecessor(const string& s, string& pred) {
        int k = s.size();
        invrep(i, k-1, 0) {
            if (s[i] > 'a') {            
                pred = s;
                pred[i] = s[i] - 1;
                rep(j,i+1,k) pred[j] = 'z';
                return true;
            }
        }
        return false;
    }
    
    void init_lps() {
        lps[0] = 0;
        rep(j,1,m) {
            int i = lps[j-1];
            while (evil[i] != evil[j] and i > 0) i = lps[i-1];
            lps[j] = evil[i] == evil[j] ? i+1 : 0;
        }
    }

    int update_evil_index(int i, int c) {
        if (evil[i] - 'a' == c) return i+1;
        while (i > 0) {
            i = lps[i-1];
            if (evil[i] - 'a' == c) return i+1;
        }
        return 0;
    }
    
    ll dp(int i, int j, bool b) {
        if (j == m) return 0LL;
        if (i == n) return 1LL;
        ll& ans = memo[i][j][b];
        if (ans != -1) return ans;
        ans = 0;
        if (b) {
            int kmax = word[i] - 'a';
            rep(k,0,kmax) {
                int jj = update_evil_index(j, k);
                ans = (ans + dp(i+1, jj, false)) % MOD;
            }
            int jj = update_evil_index(j, kmax);
            ans = (ans + dp(i+1, jj, true)) % MOD;
        } else {
            rep(k,0,26) {
                int jj = update_evil_index(j, k);
                ans = (ans + dp(i+1, jj, false)) % MOD;
            }
        }
        return ans;
    }
    
    int findGoodStrings(int n_, string s1, string s2, string evil_) {
        n = n_;
        evil = evil_;
        m = evil.size();
        init_lps();
        
        word = s2;
        rep(i,0,n) rep(j,0,m) rep(k,0,2) memo[i][j][k] = -1;
        ll ans = dp(0,0,true);

        string tmp;
        if (find_predecessor(s1, tmp)) {
            word = tmp;
            rep(i,0,n) rep(j,0,m) rep(k,0,2) memo[i][j][k] = -1;
            ll x = dp(0,0,true);
            ans = (ans + (MOD - x)) % MOD;
        }
        
        return ans;
    }
};

int main() {
    int n; string s1, s2, evil;
    cin >> n >> s1 >> s2 >> evil;
    Solution sol;
    cout << sol.findGoodStrings(n, s1, s2, evil) << '\n';
}