// tags: Dijkstra, Floyd Warshall
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;

#define MAXN 100
int N,Q;
double S[MAXN];
ll E[MAXN];
ll D[MAXN][MAXN];
ll min_dist[MAXN][MAXN];
double min_time[MAXN][MAXN];

void compute_distances_from(int source) {    
    rep(i,0,N-1) min_dist[source][i] = LLONG_MAX;
    min_dist[source][source] = 0;

    priority_queue<lli, vector<lli>, greater<lli>> pq;
    pq.push(lli(0, source));

    while (!pq.empty()) {
        lli cur = pq.top(); pq.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d > min_dist[source][u]) continue;
        rep(v,0,N-1) {
            if (D[u][v] > 0) {
                ll dd = d + D[u][v];
                if (dd <= E[source] and min_dist[source][v] > dd) {
                    min_dist[source][v] = dd;
                    pq.push(lli(dd, v));
                }
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    rep(_case,1,T) {
        
        scanf("%d%d",&N, &Q);
        rep(i,0,N-1) scanf("%lld %lf", &E[i], &S[i]);
        rep(i,0,N-1) rep(j,0,N-1) scanf("%lld", &D[i][j]);
        rep(i,0,N-1) compute_distances_from(i);

        rep(i,0,N-1) rep(j,0,N-1) {
            if (i == j) min_time[i][j] = 0.0;
            else if (min_dist[i][j] < LLONG_MAX) {
                min_time[i][j] = min_dist[i][j] / S[i];
            } else {
                min_time[i][j] = -1.0;
            }
        }

        rep(k,0,N-1) rep(i,0,N-1) rep(j,0,N-1) {
            double tik = min_time[i][k];
            double tkj = min_time[k][j];
            if (tik > -0.5 and tkj > -0.5) {
                double dt = tik + tkj;
                if (min_time[i][j] < -0.5 or min_time[i][j] > dt) {
                    min_time[i][j] = dt;
                }
            }
        }
        
        printf("Case #%d:", _case);
        while(Q--) {
            int u, v; scanf("%d%d", &u, &v);
            printf(" %lf", min_time[u-1][v-1]);
        }
        puts("");
    }
    return 0;
}