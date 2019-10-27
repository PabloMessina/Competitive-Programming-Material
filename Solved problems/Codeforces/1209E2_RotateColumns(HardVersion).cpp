// tags: DP, bitmask, precomputation, bitwise
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int N, M;
struct Column {
    vector<int> vals;
    int maxv;
    Column() {}
    Column(int n) { vals.resize(n); maxv = 0; }
    int& operator[](int i) { return vals[i]; }
    bool operator<(const Column& o) const { return maxv > o.maxv; }
};
vector<Column> cols;

int submasks[1 << 12][1 << 12];
void precompute_submasks() {
    rep(mask,0,(1<<12)-1) {
        vector<int> bit_idxs;
        for (int i=0, tmp=mask; tmp > 0; ++i, tmp>>=1) {
            if (tmp & 1) bit_idxs.push_back(i);
        }        
        int xmax = (1<<bit_idxs.size())-1;
        rep(x, 0, xmax) {
            int submask = 0;
            for (int i=0, tmp=x; tmp > 0; ++i, tmp>>=1) {
                if (tmp & 1) submask |= (1 << bit_idxs[i]);
            }
            submasks[mask][x] = submask;
        }
    }
}

int mask2class[1 << 12];
void precompute_equivalence_mask_classes() {
    rep(mask, 0, (1 << N)-1) {
        int mask_class = mask;
        int tmp = mask;
        rep(i,2,N) {
            tmp = (tmp >> 1) | ((tmp & 1) << (N-1));
            mask_class = min(mask_class, tmp);
        }
        mask2class[mask] = mask_class;
    }
}

int maxsum[12][1 << 12];
void precompute_maxsum() {
    memset(maxsum, 0, sizeof maxsum);
    rep(i,0,M-1) rep(mask,0,(1<<N)-1) {
        int mclass = mask2class[mask];
        int sum = 0;
        rep(j,0,N-1) if ((mask >> j) & 1) sum += cols[i][j];
        maxsum[i][mclass] = max(maxsum[i][mclass], sum);
    }
}

vector<int> memo;
int dp(int i, int mask) {
    int& ans = memo[mask * M + i];
    if (ans != -1) return ans;
    if (i == M-1) {
        ans = maxsum[i][mask2class[mask]];
    } else {
        ans = 0;
        int xmax = (1 << __builtin_popcount(mask))-1;
        rep(x,0,xmax) {
            int submask = submasks[mask][x];
            ans = max(ans, maxsum[i][mask2class[submask]] + dp(i+1, mask - submask));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cols.reserve(2000);
    memo.reserve((1 << 12) * 12);
    precompute_submasks();
    int T; cin >> T;
    while (T--) {
        cin >> N >> M;
        cols.clear();
        rep(i,1,M) cols.emplace_back(N);
        rep(i,0,N-1) {
            rep(j,0,M-1) {
                cin >> cols[j][i];
                cols[j].maxv = max(cols[j].maxv, cols[j][i]);
            }
        }
        if (M > N) {
            sort(cols.begin(), cols.end());
            cols.resize(N);
            M = N;
        }
        precompute_equivalence_mask_classes();
        precompute_maxsum();
        memo.assign((1 << N) * M, -1);
        cout << dp(0, (1<<N)-1) << '\n';
    }
    return 0;
}