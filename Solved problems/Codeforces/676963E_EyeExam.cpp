#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
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
signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    int xmin = -9999 * 2, xmax = 9999 * 2;
    while (N--) {
        int a, b; char c; cin >> a >> b >> c;
        a *= 2; b *= 2;
        int aa, bb;
        if (c == 'E') {
            aa = (a+b)/2;
            bb = aa;
        } else if (c == 'A') {
            aa = -9999 * 2;
            bb = (a+b)/2 - 1;
        } else {
            bb = 9999 * 2;
            aa = (a+b)/2 + 1;
        }
        xmin = max(xmin, aa);
        xmax = min(xmax, bb);
    }
    if (xmin % 2 == 1) xmin++;
    if (xmax % 2 == 1) xmax--;
    xmin /= 2;
    xmax /= 2;
    if (xmin > xmax) {
        cout << "*\n";
    } else {
        cout << xmin << ' ' << xmax << '\n';
    }
    return 0;
}