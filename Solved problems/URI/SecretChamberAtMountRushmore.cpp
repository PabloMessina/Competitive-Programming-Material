// tags: BFS
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

uset<int> vis[26];
vvi g(26);

int main() {
    int m,n;
    scanf("%d%d\n", &m, &n);
    while(m--) {
        char a, b; scanf("%c %c\n",&a,&b);
        g[a-'a'].push_back(b-'a');
    }

    queue<int> q;
    rep(i,0,25) {
        q.push(i);
        vis[i].insert(i);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for (int v: g[u]) {
                if (vis[i].count(v) == 0) {
                    vis[i].insert(v);
                    q.push(v);
                }
            }
        }
    }

    char buff1[51], buff2[51];
    loop:
    while(n--) {
        scanf("%s %s", buff1, buff2);
        string w1(buff1);
        string w2(buff2);
        if (w1.size() != w2.size()) {
            puts("no");
            continue;
        }
        int len = w1.size();
        rep(i,0,len-1) {
            if (vis[w1[i]-'a'].count(w2[i]-'a') == 0) {
                puts("no");
                goto loop;
            }
        }
        puts("yes");
    }
    return 0;
}