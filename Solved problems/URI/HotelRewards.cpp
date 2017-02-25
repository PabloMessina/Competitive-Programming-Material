// tags: greedy
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define invrep(i,a,b) for(int i=a;i>=b;--i)
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    int prices[n];
    rep(i,0,n-1) scanf("%d", &prices[i]);  
    int cost = 0;
    priority_queue<int> pq;
    invrep(i,n-1,0) {
        pq.push(prices[i]);
        cost += prices[i];
        if ((i+1) % (k+1) == 0)
            cost -= pq.top(), pq.pop();
    }
    printf("%d\n", cost);
    return 0;
}