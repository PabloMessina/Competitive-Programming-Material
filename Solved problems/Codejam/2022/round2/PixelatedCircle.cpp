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
    rep(_case, 1, T+1) {
        int R; cin >> R;
        bool correct[2*R+1][2*R+1] = {};
        bool incorrect[2*R+1][2*R+1] = {};
        // paint correctly
        rep(x,-R,R+1) rep(y,-R,R+1) if (round(sqrt(x * x + y * y)) <= R) {
            correct[R + x][R + y] = true;
        }
        // paint incorrectly
        rep(r,0,R+1) rep(x,-r,r+1) {
            int y = round(sqrt(r * r - x * x));
            incorrect[R + x][R + y] = true;
            incorrect[R + x][R - y] = true;
            incorrect[R + y][R + x] = true;
            incorrect[R - y][R + x] = true;

        }
        // compute answer
        int count = 0;
        rep(i,0,2*R+1) rep(j,0,2*R+1) if (incorrect[i][j] != correct[i][j]) count++;
        cout << "Case #" << _case << ": " << count << "\n";
    }
    return 0;
}