// tags: stacks, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
const int MAXN = 100000;
int N;
int H[MAXN], L[MAXN], R[MAXN];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    vector<pair<int,int>> _stack;
    _stack.reserve(MAXN);
    while (cin >> N) {
        rep(i,0,N-1) cin >> H[i];
        _stack.clear();
        _stack.emplace_back(INT_MAX, 0);
        rep(i,0,N-1) {
            int minh = H[i];
            while (_stack.back().first <= H[i]) {
                minh = min(minh, _stack.back().second);
                _stack.pop_back();
            }
            _stack.emplace_back(H[i], minh);
            L[i] = minh;
        }
        _stack.clear();
        _stack.emplace_back(INT_MAX, 0);
        invrep(i,N-1,0) {
            int minh = H[i];
            while (_stack.back().first <= H[i]) {
                minh = min(minh, _stack.back().second);
                _stack.pop_back();
            }
            _stack.emplace_back(H[i], minh);
            R[i] = minh;
        }
        bool f = true;
        rep(i,0,N-1) {
            int d = H[i] - max(L[i], R[i]);
            assert (d >= 0);
            if (d >= 150000) {
                if (f) f = false;
                else cout << ' ';
                cout << (i+1);
            }            
        }
        cout << '\n';
    }
    return 0;
}