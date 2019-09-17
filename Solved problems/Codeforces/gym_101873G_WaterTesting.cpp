// tags: Pick's Theorem, Polygon Area, geometry
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 100000;
int N;
ll X[MAXN], Y[MAXN];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i,0,N-1) cin >> X[i] >> Y[i];    
    ll area = 0;
    ll p_border = 0;
    for (int i = N-1, j = 0; j < N; i=j++) {
        area += (X[i] + X[j]) * (Y[j] - Y[i]);
        p_border += __gcd(abs(X[j] - X[i]), abs(Y[j] - Y[i]));
    }
    area = abs(area) >> 1;
    ll p_in = area - p_border/2 + 1;
    cout << p_in << '\n';
    return 0;
}