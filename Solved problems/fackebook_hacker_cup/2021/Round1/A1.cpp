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
        int n; string s; cin >> n >> s;
        int op1 = 0, op2 = 0;
        for (char c : s) {
            if (op1 % 2 == 0 and c == 'O') op1++;
            if (op1 % 2 == 1 and c == 'X') op1++;
            if (op2 % 2 == 0 and c == 'X') op2++;
            if (op2 % 2 == 1 and c == 'O') op2++;
        }
        cout << "Case #" << t << ": " << min(op1, op2) << '\n';
    }
    return 0;
}