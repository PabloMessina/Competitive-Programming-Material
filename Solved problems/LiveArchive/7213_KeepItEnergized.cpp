// tags: DP, range minimum query (segment tree), binary search
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
#define MAXN 100005
int N,M;
int E[MAXN], accE[MAXN];
struct Shop { int l, s, c; };
vector<Shop> shops[MAXN];

// segment tree for DP
int DP[MAXN];
int st[MAXN * 4 + 5];
int left(int x) { return x << 1; }
int right(int x) { return (x << 1) + 1; }
void build_st(int node, int l, int r) {
    if (l == r) {
        st[node] = 0;
        return;
    }
    int ln = left(node), rn = right(node);
    build_st(ln, l, (l+r)/2);
    build_st(rn, (l+r)/2+1, r);
    st[node] = min(st[ln], st[rn]);
}
void update_point(int node, int l, int r, int i, int val) {
    if (i < l or i > r) return;
    if (l == r) {
        st[node] = val;
        return;
    }
    int ln = left(node), rn = right(node);
    update_point(ln, l, (l+r)/2, i, val);
    update_point(rn, (l+r)/2+1, r, i, val);
    st[node] = min(st[ln], st[rn]);
}
int rmq(int node, int l, int r, int i, int j) {
    if (i > j or i > r or j < l) return INT_MAX;
    if (i <= l and r <= j) return st[node];
    return min(rmq(left(node),l,(l+r)/2,i,j),
               rmq(right(node),(l+r)/2+1,r,i,j));
}

// binary search
bool check(Shop& shop, int m) {
    return shop.s < accE[m-1] - (shop.l > 0 ? accE[shop.l-1] : 0);
}
int rightmost_reachable(Shop& shop) {
    int i = shop.l+1, j = N;
    while (i < j) {
        int m = (i+j)/2;
        if (check(shop, m))
            j = m;
        else
            i = m+1;
    }
    if (check(shop, i)) return i-1;
    return i;
}

int main() {
    while (scanf("%d%d", &N, &M) == 2) {
        int totE = 0;
        rep(i,0,N-1) {
            scanf("%d", &E[i]);
            accE[i] = totE = totE + E[i];
            shops[i].clear();
        }
        rep(i,1,M) {
            int l,s,c; scanf("%d%d%d",&l,&s,&c); --l;
            shops[l].push_back({l, s, c});
        }
        DP[N] = 0;
        invrep(i,N-1,0) {
            DP[i] = INT_MAX;
            for (Shop& shop : shops[i]) {
                int r = rightmost_reachable(shop);
                if (r > i) {
                    int range_min = rmq(1,0,N,i+1,r);
                    if (range_min < INT_MAX) {
                        DP[i] = min(DP[i], shop.c + range_min);
                    }
                }
            }
            update_point(1,0,N,i,DP[i]);
        }
        if (DP[0] == INT_MAX)
            puts("-1");
        else
            printf("%d\n", DP[0]);
    }
    return 0;
}