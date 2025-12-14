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
    int T; cin >> T;
    rep(t,1,T+1) {
        int N; cin >> N;
        vi X(N); rep(i,0,N) cin >> X[i];
        sort(X.begin(), X.end());
        double ans;
        if (N == 5) {
            double ans1 = ((X[N-1] + X[N-3]) - (X[0] + X[1])) * 0.5;
            double ans2 = ((X[N-1] + X[N-2]) - (X[0] + X[2])) * 0.5;
            ans = max(ans1, ans2);
        } else {
            ans = ((X[N-1] + X[N-2]) - (X[0] + X[1])) * 0.5;
        }
        cout << "Case #" << t << ": ";
        cout << fixed << setprecision(10) << ans << "\n";
    }
    return 0;
}