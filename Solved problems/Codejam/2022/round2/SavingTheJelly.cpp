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
const int MAXN = 1000;
int N;
struct P {
    ll x, y;
    ll dist2(const P& o) const {
        ll dx = x - o.x;
        ll dy = y - o.y;
        return dx * dx + dy * dy;
    }
};
P C[MAXN];
P S[MAXN+1];

ll dist2[MAXN][MAXN+1];

vector<vector<ii>> choice;
vector<vector<int>> memo;
bool dp(int cmask, int smask) {
    int& ans = memo[cmask][smask];
    if (ans != -1) return ans;
    // printf("dp(cmask=%d, smask=%d)\n", cmask, smask);
    if (cmask == 0) return ans = (smask == 1);
    ans = 0;
    rep(i,0,N) {
        if (cmask & (1 << i)) {
            ll mindist = LLONG_MAX;
            vector<int> candidates;
            rep(j,0,N+1) {
                if (smask & (1 << j)) {
                    if (dist2[i][j] < mindist) {
                        mindist = dist2[i][j];
                        candidates.clear();
                        if (j != 0) candidates.push_back(j);
                    } else if (dist2[i][j] == mindist and j != 0) {
                        candidates.push_back(j);
                    }
                }
            }
            // printf("   i = %d, candidates.size() = %d\n", i, candidates.size());
            for (int j : candidates) {
                assert (j != 0);
                // printf("   i=%d, j=%d, smask=%d, (smask & ~j) = %d\n",
                //         i, j, smask, smask & ~j);
                if (dp(cmask & ~(1 << i), smask & ~(1 << j))) {
                    choice[cmask][smask] = {i, j};
                    return ans = 1;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(_case, 1, T+1) {
        // puts("-----------------------");
        cin >> N;
        rep(i,0,N) cin >> C[i].x >> C[i].y;
        rep(i,0,N+1) cin >> S[i].x >> S[i].y;
        // init dist2
        rep(i,0,N) rep(j,0,N+1) dist2[i][j] = C[i].dist2(S[j]);
        int cmask = (1 << N) - 1;
        int smask = (1 << (N+1)) - 1;
        // printf("cmask = %d, smask = %d\n", cmask, smask);
        memo.assign(cmask+1, vi(smask+1,-1));
        choice.assign(cmask+1, vector<ii>(smask+1));
        if (dp(cmask, smask)) {
            cout << "Case #" << _case << ": POSSIBLE\n";
            while (cmask) {
                ii p = choice[cmask][smask];
                cout << (p.ff + 1) << ' ' << (p.ss + 1) << '\n';
                cmask = cmask & ~(1 << p.ff);
                smask = smask & ~(1 << p.ss);
            }
            assert (smask == 1);
        } else {
            cout << "Case #" << _case << ": IMPOSSIBLE\n";
        }
    }
    return 0;
}