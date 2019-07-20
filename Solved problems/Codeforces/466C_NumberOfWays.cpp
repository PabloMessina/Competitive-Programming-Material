// tags: DP, counting
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

const int MAXN = 500000;
ll a[MAXN];
ll acc[MAXN];
ll counts[MAXN];

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    ll sum = 0;
    rep(i,0,n-1) {
        cin >> a[i];
        sum += a[i];
        acc[i] = sum;
    }
    if (sum % 3 != 0 or n < 3) {
        cout << "0\n";
    } else {
        ll ans = 0;
        ll one_third = sum/3;
        ll two_thirds = sum*2/3;
        ll c = 0;
        rep(i,0,n-1) {
            if (acc[i] == two_thirds) c++;
            counts[i] = c;
        }
        rep(i,0,n-3) {
            if (acc[i] == one_third) {
                ans += (counts[n-2] - counts[i]);
            }
        }
        cout << ans << '\n';
    }    
    return 0;
}