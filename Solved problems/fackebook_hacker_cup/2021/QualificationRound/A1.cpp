#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    set<char> vocals = {'A', 'E', 'I', 'O', 'U'};
    int T; cin >> T;
    rep(t,1,T+1) {
        string s; cin >> s;
        int ans = INT_MAX;
        rep(i,0,26) {
            int count = 0;
            bool i_vocal = vocals.count(i + 'A');
            for (char c : s) {
                int j = c - 'A';
                if (i == j) continue;
                bool j_vocal = vocals.count(c);
                if (i_vocal == j_vocal) count += 2;
                else count++;
                                                
            }
            ans = min(ans, count);
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}