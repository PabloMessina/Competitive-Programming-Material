// tags: fenwick tree, sorting queries
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define umap unordered_map
// -------------------------------
const int MAXN = 500000;
int N;
struct Lady {
    int b, i, r;
    bool operator<(const Lady& o) const {
        if (b != o.b) return b > o.b;
        return i > o.i;
    }
} ladies[MAXN];

struct BIT { // binary indexed tree (a.k.a. Fenwick Tree)
    vector<int> bit;
    BIT(int n) { bit.assign(n+1, 0); }
    int query(int k) {
        int ans = 0;
        for (; k; k -= (k & -k)) ans = max(ans, bit[k]);
        return ans;
    }
    void update(int k, int v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] = max(bit[k], v);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0); // ignoren esto
    cin >> N;
    set<int> iset;
    rep(i,0,N) cin >> ladies[i].b;
    rep(i,0,N) {
        int tmp; cin >> tmp; tmp = -tmp;
        ladies[i].i = tmp;
        iset.insert(tmp);
    }
    rep(i,0,N) cin >> ladies[i].r;
    int ID = 1;
    umap<int,int> i2id;
    for (int i : iset) i2id[i] = ID++;
    BIT bit(ID); // nuestro segundo arreglo de paint
    sort(ladies, ladies + N);
    int cnt = 0;
    rep(i,0,N) {
        Lady& l = ladies[i];
        if (l.r < bit.query(i2id[l.i]-1)) cnt++;
        else bit.update(i2id[l.i], l.r);
    }
    cout << cnt << '\n';
    return 0;
}