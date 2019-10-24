// tags: implementation, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
vector<int> R, output, output_tmp;
vector<int> parent;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int N, D; cin >> N >> D;
    R.resize(N);
    parent.resize(N);
    output.assign(D, 0);
    output_tmp.resize(D);
    rep(i,0,N-1) cin >> R[i];
    rep(i,0,N-1) {
        cin >> parent[i];
        if (parent[i] != -1) --parent[i];
    }
    rep(i,0,N-1) {
        int u = i;
        bool valid = true;
        invrep(j, D-1, 0) {
            if (u == -1) { valid = false; break; }
            output_tmp[j] = R[u];
            u = parent[u];
        }
        if (!valid) continue;
        bool better = true;
        rep(j,0,D-1) {
            if (output[j] < output_tmp[j]) break;
            if (output[j] > output_tmp[j]) { better = false; break; }
        }
        if (better) output.swap(output_tmp);
    }
    rep(i,0,D-1) {
        if (i) cout << ' ';
        cout << output[i];
    }
    cout << '\n';
    return 0;
}