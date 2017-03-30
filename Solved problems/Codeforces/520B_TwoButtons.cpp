// tags: Dijkstra, Implicit Graph
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef pair<int,int> ii;

int min_dist[10001];

int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    if (n >= m) {
        printf("%d\n",n-m);
    } else {
        rep(i,1,m) min_dist[i] = INT_MAX;
        min_dist[n] = 0;
        priority_queue<ii, vector<ii>, greater<ii>> pq;
        pq.push(ii(0,n));
        while (!pq.empty()) {
            ii p = pq.top(); pq.pop();
            int dist = p.first;
            int u = p.second;

            if (dist > min_dist[u])
                continue;

            int v, d;
            if (u > 1) {
                d = dist + 1;
                v = u - 1;
                if (d < min_dist[v]) {
                    min_dist[v] = d;
                    if (v != m) pq.push(ii(d,v));
                }                    
            }

            if (2 * u >= m) {
                v = m, d = dist + 1 + (2 * u - m);
            } else {
                v = 2 * u, d = dist + 1;
            }
            if (d < min_dist[v]) {
                min_dist[v] = d;
                if (v != m) pq.push(ii(d,v));
            }
        }
        printf("%d\n", min_dist[m]);
    }
    return 0;
}