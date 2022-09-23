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
    rep(_t,1,T+1) {
        int n, k; cin >> n >> k;
        vector<int> A(n), B(n);
        rep(i,0,n) cin >> A[i];
        rep(i,0,n) cin >> B[i];
        int offset;
        rep(i,0,n) if (B[i] == A[0]) { offset = i; break; }
        bool equal = true;
        rep(i,0,n) if (A[i] != B[(i + offset) % n]) { equal = false; break; }
        cout << "Case #" << _t << ": ";
        if (not equal) {
            cout << "NO\n";
        } else {
            if (k == 0) {
                if (offset == 0) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            } else if (k == 1) {
                if (offset == 0) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                }
            } else {
                if ((k % 2) == 0) {
                    if (offset == 0) {
                        cout << "YES\n";
                    } else if (n > 2) {
                        cout << "YES\n";
                    } else {
                        cout << "NO\n";
                    }
                } else {
                    if (offset > 0) {
                        cout << "YES\n";
                    } else if (n > 2) {
                        cout << "YES\n";
                    } else {
                        cout << "NO\n";
                    }
                }
            }
        }
    }
    return 0;
}