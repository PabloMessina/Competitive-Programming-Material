// tags: BFS, GCD
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define uset unordered_set 
typedef pair<int,int> ii;

#define MAXI 10000
#define MAXC 100000

int I,S;
int candies[MAXI];
vector<vector<int>> g;
uset<int> found_nums;
set<ii> states;

int gcd(int a, int b) {
    int tmp;
    while (b) tmp = a, a = b, b = tmp % b;
    return a;
}

int main() {
    while (scanf("%d%d",&I,&S)==2) {
        g.assign(I, vector<int>());
        rep(i,0,I-1) scanf("%d", &candies[i]);
        rep(i,1,S) {
            int a, b; scanf("%d%d",&a,&b); --a, --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        queue<ii> q;        
        found_nums.clear();
        states.clear();
        rep(i,0,I-1) {
            ii state(i, candies[i]);
            q.push(state);
            states.insert(state);
            found_nums.insert(candies[i]);
        }
        while (!q.empty()) {
            ii front = q.front(); q.pop();
            int u = front.first, c = front.second;
            for (int v : g[u]) {
                int cc = gcd(candies[v], c);
                ii state(v, cc);
                if (!states.count(state)) {
                    states.insert(state);
                    found_nums.insert(cc);
                    q.push(state);
                }
            }
        }
        printf("%d\n", (int)found_nums.size());
    }
    return 0;
}