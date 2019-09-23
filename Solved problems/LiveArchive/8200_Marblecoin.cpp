// tags: greedy, suffix array, counting sort, radix sort, strings
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------

const int MAXN = 5 * 100000;
const ll MOD = (ll)1e9 + 7;

namespace SA { // suffix array
    int n;
    int rank[MAXN], rank_tmp[MAXN];
    int sa[MAXN], sa_tmp[MAXN];
    int inline get_rank(int i) { return i < n ? rank[i]: 0; }
    
    void counting_sort(int maxv, int k) {
        static int counts[MAXN];
        memset(counts, 0, sizeof(int) * (maxv+1));
        rep(i,0,n-1) counts[get_rank(i+k)]++;
        rep(i,1,maxv) counts[i] += counts[i-1];
        invrep(i,n-1,0) sa_tmp[--counts[get_rank(sa[i]+k)]] = sa[i];
        swap(sa, sa_tmp);
    }
    
    void sort_suffix_indexes(vector<int>& word, int maxv, vector<int>& suffix_indexes) {
        n = word.size();
        rep(i,0,n-1) { sa[i] = i; rank[i] = word[i]; }
        for (int h=1; h < n; h <<= 1) {
            counting_sort(maxv, h);
            counting_sort(maxv, 0);
            int r = 1;
            rank_tmp[sa[0]] = r;
            rep(i,1,n-1) {
                if (rank[sa[i]] != rank[sa[i-1]] or
                    get_rank(sa[i]+h) != get_rank(sa[i-1]+h)) r++;
                rank_tmp[sa[i]] = r;
            }
            swap(rank, rank_tmp);
            maxv = r;
        }
        suffix_indexes.resize(n);
        rep(i,0,n-1) suffix_indexes[i] = sa[i];
    }
}

struct Stack { int offset, size; } stacks[MAXN];
vector<int> word;
vector<int> suffix_indexes;

struct Item {
    int val, si, idx, rank;
    bool operator<(const Item& o) const { return rank > o.rank; }
} items[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);    
    word.reserve(MAXN);
    suffix_indexes.reserve(MAXN);
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
        SA::sort_suffix_indexes(word, 301, suffix_indexes);
        rep(i,0,offset-1) items[suffix_indexes[i]].rank = i;
        priority_queue<Item> pq;
        rep(i,0,N-1) pq.push(items[stacks[i].offset]);        
        ll ans = 0;
        while (count--) {
            Item cur = pq.top(); pq.pop();
            ans = ((ans + cur.val) * 400ll) % MOD;
            if (cur.idx < stacks[cur.si].size) {
                pq.push(items[stacks[cur.si].offset + cur.idx + 1]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}