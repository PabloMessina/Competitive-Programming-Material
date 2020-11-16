// tags: greedy, suffix array, counting sort, radix sort, strings
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
struct SA {
    int n;
    vector<int> counts, rank, rank_, sa, sa_;
    inline int gr(int i) { return i < n ? rank[i]: 0; }
    void csort(int maxv, int k) {
        counts.assign(maxv+1, 0);
        rep(i,0,n) counts[gr(i+k)]++;
        rep(i,1,maxv+1) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_[--counts[gr(sa[i]+k)]] = sa[i];
        sa.swap(sa_);
    }
    void get_sa(vector<int>& s) {
        rep(i,0,n) sa[i] = i;
        sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });
        int r = rank[sa[0]] = 1;
        rep(i,1,n) rank[sa[i]] = (s[sa[i]] != s[sa[i-1]]) ? ++r : r;
        for (int h=1; h < n and r < n; h <<= 1) {
            csort(r, h); csort(r, 0); r = rank_[sa[0]] = 1;
            rep(i,1,n) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    gr(sa[i]+h) != gr(sa[i-1]+h)) ++r;
                rank_[sa[i]] = r;
            } rank.swap(rank_);
        }
    }
    SA(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_.resize(n);
        sa.resize(n); sa_.resize(n);
        get_sa(s);
    }
};

const int MAXN = 5 * 100000;
const ll MOD = 1000000007;
struct Stack { int offset, size; } stacks[MAXN];
vector<int> word;
vector<int> suffix_indexes;
struct Item {
    int val, si, idx, rank;
    bool operator<(const Item& o) const { return rank > o.rank; }
} items[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    word.reserve(MAXN);
    int N;
    while (cin >> N) {
        word.clear();
        int offset = 0;
        int count = 0;
        rep(i,0,N) {
            int k; cin >> k;
            stacks[i] = { offset, k };
            rep(j,0,k) {
                int val; cin >> val;
                word.push_back(val);
                items[offset + j] = { val, i, j, 0 };
            }
            word.push_back(301);
            offset += k + 1;
            count += k;
        }
        SA sa(word);
        rep(i,0,offset) items[sa.sa[i]].rank = i;
        priority_queue<Item> pq;
        rep(i,0,N) pq.push(items[stacks[i].offset]);
        ll ans = 0;
        while (count--) {
            Item cur = pq.top(); pq.pop();
            ans = ((ans + cur.val) * 365ll) % MOD;
            if (cur.idx < stacks[cur.si].size) {
                pq.push(items[stacks[cur.si].offset + cur.idx + 1]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}