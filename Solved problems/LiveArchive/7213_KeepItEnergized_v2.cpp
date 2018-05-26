// tags: Dijkstra modified, implicit graph
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 100000;
int N,M;
int E[MAXN+1];
int accE[MAXN+1];
struct Shop { int level, strength, cost; };
vector<Shop> shops[MAXN+1];

int main() {
    while (scanf("%d%d", &N, &M) == 2) {
        accE[0] = 0;
        rep(i,1,N) {
            scanf("%d", E+i);
            accE[i] = accE[i-1] + E[i];
        }
        while(M--) {
            int l, s, c; scanf("%d%d%d", &l, &s, &c);
            shops[l].push_back({l, s, c});
        }
        int ans = -1;
        priority_queue<iii, vector<iii>, greater<iii>> q;
        int i = 0;
        int last_l = 1;
        for (Shop& shop : shops[last_l]) {
            q.emplace(shop.cost, shop.level, i++);
        } 
        while (!q.empty()) {
            iii t = q.top(); q.pop();
            int acc_cost, l, i;
            tie(acc_cost, l, i) = t;            
            Shop& curr_shop = shops[l][i];
            if (accE[l-1] + curr_shop.strength >= accE[N]) {
                ans = acc_cost;
                break;
            }
            while (accE[l-1] + curr_shop.strength >= accE[last_l]) {
                last_l++;
                int j = 0;
                for (Shop& shop : shops[last_l]) {
                    q.emplace(acc_cost + shop.cost, shop.level, j++);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}