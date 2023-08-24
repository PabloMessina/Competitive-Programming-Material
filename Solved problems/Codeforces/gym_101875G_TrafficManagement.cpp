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
int N;
const int MAXN = 1e5 + 5;
ii SV[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    rep(i,0,N) cin >> SV[i].ff >> SV[i].ss;
    sort(SV, SV + N);
    int j = N-1;
    double ans = 0;
    invrep(i,N-2,0) {
        if (SV[j].ss >= SV[i].ss) {
            j = i;
        } else {
            ans = max(ans, (double)(SV[j].ff - SV[i].ff) / (SV[i].ss - SV[j].ss));
        }
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}