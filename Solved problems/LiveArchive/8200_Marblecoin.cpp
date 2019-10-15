// tags: greedy, suffix array, counting sort, radix sort, strings
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
struct SuffixArray {
    int n;
    vector<int> counts, rank, rank_tmp, sa, sa_tmp;
    inline int get_rank(int i) { return i < n ? rank[i]: 0; }
    void counting_sort(int maxv, int k) {
        counts.assign(maxv+1, 0);
        rep(i,0,n-1) counts[get_rank(i+k)]++;
        rep(i,1,maxv) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_tmp[--counts[get_rank(sa[i]+k)]] = sa[i];
        sa.swap(sa_tmp);
    }
    void compute_sa(vector<int>& s) {
        rep(i,0,n-1) sa[i] = i;
        sort(sa.begin(), sa.end(), [&s](int i, int j) { return s[i] < s[j]; });
        int r = rank[sa[0]] = 1;
        rep(i,1,n-1) rank[sa[i]] = (s[sa[i]] != s[sa[i-1]]) ? ++r : r;
        for (int h=1; h < n and r < n; h <<= 1) {
            counting_sort(r, h);
            counting_sort(r, 0);
            r = rank_tmp[sa[0]] = 1;
            rep(i,1,n-1) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    get_rank(sa[i]+h) != get_rank(sa[i-1]+h)) ++r;
                rank_tmp[sa[i]] = r;
            }
            rank.swap(rank_tmp);
        }
    }
    SuffixArray(vector<int>& s) {
        n = s.size();
        rank.resize(n); rank_tmp.resize(n);
        sa.resize(n); sa_tmp.resize(n);
        compute_sa(s);
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
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    word.reserve(MAXN);
    int N;
    while (cin >> N) {
        word.clear();
        int offset = 0;
        int count = 0;
        rep(i,0,N-1) {
            int k; cin >> k;
            stacks[i] = { offset, k };
            rep(j,0,k-1) {
                int val; cin >> val;
                word.push_back(val);
                items[offset + j] = { val, i, j, 0 };
            }
            word.push_back(301);
            offset += k + 1;
            count += k;
        }
        SuffixArray sa(word);
        rep(i,0,offset-1) items[sa.sa[i]].rank = i;
        priority_queue<Item> pq;
        rep(i,0,N-1) pq.push(items[stacks[i].offset]);        
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