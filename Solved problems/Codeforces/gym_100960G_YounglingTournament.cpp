// tags: fenwick tree, binary search, sorting queries
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 100000;
const int MAXM = 50000;
int N, M;
ll F[MAXN];
int curr_idx[MAXN];
int update_idx[MAXM];

struct BIT {
    vector<ll> bit;
    BIT(int n) {
        bit.assign(n+1,0);
    }
    void add(int k, ll v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
    ll psq(int k) {
        ll sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
};

int count_winners(BIT& bit, int start) {
    int count = 1;
    int limit = N+M+1;
    while (start < limit) {
        int l = start+1;
        int r = limit;        
        ll ref = bit.psq(l-1);
        while (l < r) {
            int m = (l+r) >> 1;
            if (2 * ref <= bit.psq(m)) {
                r = m;
            } else {
                l = m+1;
            }
        }
        if (l < limit and 2 * bit.psq(l-1) <= bit.psq(l)) {
            count++;            
        }
        start = l;
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    // ---- N players
    cin >> N;    
    vector<tuple<ll,int,bool>> tuples; // (force, index, is_update)
    rep(i,0,N-1) { // for each player
        cin >> F[i];
        tuples.emplace_back(F[i],i,false);
    }
    // ---- M udpates
    cin >> M;
    vector<pair<int,ll>> updates; // (index, force)
    rep(i,0,M-1) { // for each update
        int k; ll f;
        cin >> k >> f; k--;
        tuples.emplace_back(f,i,true);
        updates.emplace_back(k,f);
    }
    sort(tuples.begin(), tuples.end());
    int idx = 1;
    set<int> active_idxs;
    for (auto& t : tuples) {
        int i = get<1>(t);
        bool is_update = get<2>(t);
        if (is_update) {
            update_idx[i] = idx;
        } else {
            curr_idx[i] = idx;
            active_idxs.insert(idx);
        }
        idx++;
    }
    BIT bit(N+M);
    rep(i,0,N-1) {        
        bit.add(curr_idx[i], F[i]);
    }
    cout << count_winners(bit, *active_idxs.begin()) << '\n';
    rep(i,0,M-1) {
        int k; ll f; tie(k,f) = updates[i];
        bit.add(curr_idx[k], -F[k]);
        active_idxs.erase(curr_idx[k]);
        curr_idx[k] = update_idx[i];
        active_idxs.insert(curr_idx[k]);
        F[k] = f;
        bit.add(curr_idx[k], F[k]);
        cout << count_winners(bit, *active_idxs.begin()) << '\n';
    }
    return 0;
}