#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const ll MOD =  1000000007;
ll inline mul(ll a, ll b) { return (a*b)%MOD; }
ll inline add(ll a, ll b) { return (a+b)%MOD; }

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int T; ll a,b,c,n;
    cin >> T;
    while (T--) {
        cin >> a >> b >> c >> n;
        priority_queue<ll> lower;
        priority_queue<ll, vector<ll>, greater<ll>> upper;
        ll sum = 1;
        lower.push(1);
        rep(i,2,n) {
            ll median = lower.top();
            ll x = add(add(mul(a,median),mul(b,i)),c);
            sum += x;
            if (x > median) {
                upper.push(x);
                if (upper.size() > lower.size()) {
                    lower.push(upper.top());
                    upper.pop();
                }
            } else {
                lower.push(x);
                if (lower.size() > upper.size() + 1) {
                    upper.push(lower.top());
                    lower.pop();
                }
            }
        }
        cout << sum << '\n';
    }
    return 0;
}