#include <bits/stdc++.h>
// tags: bit, fenwick tree, range query
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

struct BIT {
    int n; vi f;
    BIT(int n) {
        this->n = n;
        this->f.assign(n+1, 0);
    }
    void add(int x, int d) {
        while (x <= n) {
            f[x] += d;
            x += x & -x;
        }
    }
    int psq(int x) {
        int sum = 0;
        while (x) {
            sum += f[x];
            x -= x & -x;
        }
        return sum;
    }
    int rsq(int i, int j) {
        return psq(j) - psq(i-1);
    }
};

int main() {
    int n;
    string line;
    vi ohms;
    int _case = 1;
    while(true) {
        scanf("%d", &n);
        if (n == 0) break;

        ohms.resize(n+1);
        BIT ft(n);

        rep(i,1,n) {
            int x; scanf("%d\n", &x);
            ohms[i] = x;
            ft.add(i,x);
        }

        if (_case > 1) puts("");
        printf("Case %d:\n", _case);

        while (true) {
            getline(cin, line);
            if (line[0] == 'S') {
                int x, r; sscanf(line.c_str() + 1, "%d%d", &x, &r);                
                int delta = r - ohms[x];
                ohms[x] = r;
                ft.add(x, delta);
            } else if (line[0] == 'M') {
                int x, y; sscanf(line.c_str() + 1, "%d%d", &x, &y);
                printf("%d\n", ft.rsq(x,y));
            } else {
                break;                
            }
        }

        _case++;
    }
    return 0;
}