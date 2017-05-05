// tags: sorting, median, minimum absolute deviation
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

int main() {
    int n, m, d, nm;
    scanf("%d%d%d", &n, &m, &d);
    nm = n * m;
    int a[nm];
    rep(i,0,nm-1) scanf("%d", &a[i]);
    sort(a, a+nm);
    bool ok = true;
    rep(i,1,nm-1) {
        if ((a[i] - a[i-1]) % d > 0) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        puts("-1");
    } else {
        int median = a[nm/2];
        int count = 0;
        rep(i, 0, nm-1) {
            count += abs(a[i] - median) / d;
        }
        printf("%d\n", count);
    }
    return 0;
}