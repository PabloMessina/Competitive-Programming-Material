// tags: DP, divide & conquer optimization
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
typedef long long int ll;

#define MAXL 8000
#define MAXG 800
int L, G;
ll crazy[MAXL];
ll crazy_sum[MAXL];
ll memo[MAXG+1][MAXL+1];

ll cost(int i, int j) {
    return (j - i + 1) * (crazy_sum[j] - (i>0 ? crazy_sum[i-1] : 0));
}

void dp(int g, int l1, int l2, int k1, int k2) {
    if (l1 > l2) return;
    int lm = (l1+l2)/2;
    int kmin = max(g-1, k1);
    int kmax = min(lm-1, k2);
    ll ans = LLONG_MAX;
    int best_k;
    rep(k,kmin,kmax) {
        ll tmp = memo[g-1][k] + cost(k, lm-1);
        if (ans > tmp) ans = tmp, best_k = k;
    }
    memo[g][lm] = ans;
    dp(g, l1, lm-1, k1, best_k);
    dp(g, lm+1, l2, best_k, k2);
}

int main() {
    scanf("%d%d",&L,&G);
    if (G > L) G = L;
    ll prev = 0;
    rep(i,0,L-1) {
        scanf("%lld",&crazy[i]);
        prev = crazy_sum[i] = prev + crazy[i];
    }
    rep(l,1,L) memo[1][l] = cost(0,l-1);
    rep(g,2,G) dp(g,g,L,1,L);
    printf("%lld\n", memo[G][L]);
    return 0;
}