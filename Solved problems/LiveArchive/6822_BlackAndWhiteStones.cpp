#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    ll a, b;
    while (cin >> a >> b) {
        b = a - b;
        string s; cin >> s;
        int count = 0, n = s.size();
        for (char c : s) if (c == 'B') count++;
        int i = count - 1, j = count;
        ll ans = 0;
        while (true) {
            while (i >= 0 and s[i] == 'B') --i;
            while (j < n and s[j] == 'W') ++j;
            if (i < 0 or j >= n) break;
            ans += min((j-i) * b, a);
            --i, ++j;
        }
        cout << ans << '\n';
    }
    return 0;
}