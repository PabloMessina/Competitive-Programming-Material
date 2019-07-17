// tags: math
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
typedef long long int ll;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll a,b,c; cin >> a >> b >> c;
    bool possible;
    if (c == 0) {
        possible = a == b;
    } else if ((b-a) % c == 0) {
        possible = (b - a) / c >= 0;
    } else {
        possible = false;
    }
    if (possible) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}