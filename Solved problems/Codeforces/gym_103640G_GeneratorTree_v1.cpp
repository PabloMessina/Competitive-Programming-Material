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
const int MAXN = 200000;
int N;
vector<vector<ii>> trees[MAXN];
vector<ii> edges[MAXN];
vector<pair<ll,int>> memo;
umap<int,uset<int>> isomorphic;
umap<ll, int> hash2treeid;
int global_d;
int subtree_id;
 
vector<int> get_divisors(int n) {
    vector<int> divs;
    int x;
    for (x = 1; x*x < n; ++x) {  
        if (n % x == 0) {
            divs.push_back(x);
            divs.push_back(n/x);
        }
    }
    if (x * x == n) divs.push_back(x);
    return divs;
}
 
ll B = 1777771, M[2] = {999727999, 1070777777};
ll MASK32 = (1LL << 32) - 1LL;
vector<ll> H[2];
void init_hash() {
    rep(i,0,2) {
        H[i].resize(1e6);
        H[i][0] = 1;
        rep(j,1,1e6) H[i][j] = (H[i][j-1] * B) % M[i];
    }
}
 
pair<ll, int> get_hash(vector<pair<ll,int>>& hashes) {    
    ll h0 = 0, h1 = 0; int count = 0;
    // open parenthesis
    h0 += 1, h1 += 1, count += 1;
    // sub hashes
    for (auto& x : hashes) {
        h0 = ((h0 * H[0][x.ss]) % M[0] + (x.ff >> 32)) % M[0];
        h1 = ((h1 * H[1][x.ss]) % M[1] + (x.ff & MASK32)) % M[1];
        count += x.ss;
    }
    // close parenthesis
    h0 = ((h0 * H[0][1]) % M[0] + 2) % M[0];
    h1 = ((h1 * H[1][1]) % M[1] + 2) % M[1];
    count += 1;
    return make_pair((h0 << 32) | h1, count);
}
 
tuple<ll, int, int> dfs(vector<vector<ii>>& tree, int u, int p) {
    vector<pair<ll, int>> hashes;
    hashes.reserve(tree[u].size());
    int count = 1;
    for (auto& x : tree[u]) {
        if (x.ff == p) continue;
        auto ret = dfs(tree, x.ff, u);
        if (subtree_id == -2) return {-1, -1, -1};
        int size = get<2>(ret);
        if (size == global_d) continue;
        count += size;
        hashes.emplace_back(get<0>(ret), get<1>(ret));
    }
    sort(hashes.begin(), hashes.end());
    auto h = get_hash(hashes);
    if (count == global_d) {
        auto it = hash2treeid.find(h.ff);
        if (it != hash2treeid.end()) {
            if (subtree_id == -1) subtree_id = it->ss;
            else if (subtree_id != it->ss) {
                subtree_id = -2;
                return {-1, -1, -1};
            }
        } else {
            subtree_id = -2;
            return {-1, -1, -1};
        }
    }
    if (count > global_d) {
        subtree_id = -2;
        return {-1, -1, -1};
    }
    return make_tuple(h.ff, h.ss, count);
}
 
void decompose(int tree_id, int d) {
    global_d = d;
    vector<vector<ii>>& tree = trees[tree_id];
    dfs(tree, 0, -1);
}
 
pair<ll,int> dp(int idx, int u, int p, int e) {
    if (p == -1) {
        vector<vector<ii>>& tree = trees[idx];
        vector<pair<ll, int>> hashes;
        hashes.reserve(tree[u].size());
        for (auto& x : tree[u]) {
            auto h = dp(idx, x.ff, u, x.ss);
            hashes.push_back(h);
        }
        sort(hashes.begin(), hashes.end());
        return get_hash(hashes);
    } else {
        int d = edges[idx][e].ff == p;
        auto& ans = memo[2 * e + d];
        if (ans.ff != -1) return ans;
        vector<vector<ii>>& tree = trees[idx];
        vector<pair<ll, int>> hashes;
        hashes.reserve(tree[u].size());
        for (auto& x : tree[u]) {
            if (x.ff == p) continue;
            auto h = dp(idx, x.ff, u, x.ss);
            hashes.push_back(h);
        }
        sort(hashes.begin(), hashes.end());
        return ans = get_hash(hashes);
    }
}
 
void update_hashes(int tree_id) {
    vector<vector<ii>>& tree = trees[tree_id];
    int n = tree.size();
    memo.assign(n * 2, {-1, -1});
    rep(u,0,n) {
        auto h = dp(tree_id, u, -1, -1);
        auto it = hash2treeid.find(h.ff);
        if (it == hash2treeid.end()) {
            hash2treeid[h.ff] = tree_id;
            isomorphic[tree_id].insert(tree_id);
        } else if (tree_id != it->ss) {
            isomorphic[it->ss].insert(tree_id);
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    // precompute stuff for hashing
    init_hash();
    // read trees from input
    int maxk = 0;
    rep(i,0,N) {
        int k; cin >> k;
        maxk = max(k, maxk);
        vector<vector<ii>>& tree = trees[i];
        vector<ii>& e = edges[i];
        tree.resize(k);
        e.reserve(k);
        rep(j,0,k-1) {
            int u, v; cin >> u >> v; --u, --v;
            tree[u].eb(v, j);
            tree[v].eb(u, j);
            e.eb(u, v);
        }
    }
    // sort trees by size
    vi idxs(N);
    rep(i,0,N) idxs[i] = i;
    sort(idxs.begin(), idxs.end(), [](int i, int j) {
        return trees[i].size() < trees[j].size();
    });    
    // compute answers
    vector<bool> seen_sizes(maxk + 1, false);
    memo.reserve(maxk * 2);
    vi answers(N, 0);
    int i = 0;
    while (i < N) {
        // [i, j] -> trees of the same size
        int j = i;
        while (j + 1 < N and trees[idxs[i]].size() == trees[idxs[j+1]].size()) ++j;
        rep(k,i,j+1) {
            int idx = idxs[k];
            vector<vector<ii>>& tree = trees[idx];
            vi divs = get_divisors(tree.size());
            for (int d : divs) { // for each divisor of trees[idx].size()
                if (seen_sizes[d]) {
                    subtree_id = -1;
                    decompose(idx, d);
                    assert (subtree_id != -1);
                    if (subtree_id != -2) answers[idx] += isomorphic[subtree_id].size();
                }
            }
        }
        // update hashes with current batch of trees
        rep(k,i,j+1) {
            int idx = idxs[k];
            vector<vector<ii>>& tree = trees[idx];
            seen_sizes[tree.size()] = true;
            update_hashes(idx);            
        }
        i = j+1;
    }
    // update answers with isomorphic trees
    for (auto& kv : isomorphic) {
        for (int i : kv.second) answers[i] += kv.second.size() - 1;
    }
    // print answers
    rep(i,0,N) {
        if (i) cout << ' ';
        cout << answers[i];
    }
    cout << '\n';
    return 0;
}