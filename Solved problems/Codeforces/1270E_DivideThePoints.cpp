// tags: math, geometry, number theory
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
const int MAXN = 1000;
int x[MAXN], y[MAXN];
int offset = (int)1e6;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    rep(i,0,n) {
        cin >> x[i] >> y[i];
        x[i] += offset;
        y[i] += offset;
    }
    while (1) {
        int c00 = 0, c01 = 0, c10 = 0, c11 = 0;
        rep(i,0,n) {
            bool x_odd = x[i] & 1;
            bool y_odd = y[i] & 1;
            if (x_odd and y_odd) c11++;
            else if (x_odd and not y_odd) c10++;
            else if (not x_odd and y_odd) c01++;
            else c00++;
        }
        int c1 = c10 + c01;
        int c0 = c00 + c11;
        if (c0 > 0 and c1 > 0) {
            cout << c1 << '\n';
            bool f = true;
            rep(i,0,n) {
                if ((x[i] + y[i]) & 1) {
                    if (f) f = false;
                    else cout << ' ';
                    cout << i+1;
                }
            }
            cout << '\n';
            break;
        } else if (c00 > 0 and c11 > 0) {
            cout << c11 << '\n';
            bool f = true;
            rep(i,0,n) {
                if ((x[i]&1) and (y[i]&1)) {
                    if (f) f = false;
                    else cout << ' ';
                    cout << i+1;
                }
            }
            cout << '\n';
            break;
        } else if (c10 > 0 and c01 > 0) {
            cout << c10 << '\n';
            bool f = true;
            rep(i,0,n) {
                if ((x[i]&1) and not (y[i]&1)) {
                    if (f) f = false;
                    else cout << ' ';
                    cout << i+1;
                }
            }
            cout << '\n';
            break;
        }
        rep(i,0,n) x[i] /= 2, y[i] /= 2;
    }
    return 0;
}