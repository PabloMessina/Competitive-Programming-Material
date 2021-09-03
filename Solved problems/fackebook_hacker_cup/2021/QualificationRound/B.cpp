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
        int N; cin >> N;
        vector<string> board(N);
        for (string& s : board) cin >> s;
        vector<int> RX(N), CX(N), RO(N), CO(N);
        rep(r,0,N) rep(c,0,N) {
            if (board[r][c] == 'X') {
                RX[r]++;
                CX[c]++;
            } else if (board[r][c] == 'O') {
                RO[r]++;
                CO[c]++;
            }
        }
        int minc = INT_MAX;
        set<vector<int>> dups;
        int B; ll P = 1e9 + 21;
        rep(i,0,N) {
            if (RO[i] == 0) {
                int c = N - RO[i] - RX[i];                
                vector<int> x;
                rep(j,0,N) {
                    if (board[i][j] == '.') {
                        x.emplace_back(i * N + j);
                    }
                }
                sort(x.begin(), x.end());                
                if (minc > c) {
                    minc = c;
                    dups.clear(); dups.insert(x);
                } else if (minc == c) {
                    dups.insert(x);
                }
            }
            if (CO[i] == 0) {
                int c = N - CO[i] - CX[i];
                vector<int> x;
                rep(j,0,N) {
                    if (board[j][i] == '.') {
                        x.emplace_back(j * N + i);
                    }
                }
                sort(x.begin(), x.end());
                if (minc > c) {
                    minc = c;
                    dups.clear(); dups.insert(x);
                } else if (minc == c) {
                    dups.insert(x);
                }
            }
        }
        cout << "Case #" << t << ": ";
        if (minc == INT_MAX) {
            cout << "Impossible\n";
        } else {
            cout << minc << ' ' << dups.size() << '\n';
        }
    }
    return 0;
}