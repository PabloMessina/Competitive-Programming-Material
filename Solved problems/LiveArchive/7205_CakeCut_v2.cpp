// tags: polygon area, ternary search
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
int N;
struct Point { ll x,y; };
Point pts[MAXN];
ll acc_area[MAXN];

ll get_area(int i, int j) {
    ll area;
    if (i < j) {
        area = acc_area[j-1];
        if (i > 0) area -= acc_area[i-1];
    } else {
        area = acc_area[N-1] - acc_area[i-1];
        if (j > 0) area += acc_area[j-1];
    }
    area += (pts[i].x + pts[j].x) * (pts[i].y - pts[j].y);
    return area;
}

bool predicate(ll tot_area, int i, int j) {
    ll tmp = get_area(i,j);
    ll val1 = max(tmp, tot_area - tmp);
    tmp = get_area(i,(j+1)%N);
    ll val2 = max(tmp, tot_area - tmp);
    return val1 <= val2;
}

int main() {
    while (scanf("%d", &N) == 1) {
        rep(i,0,N-1) scanf("%lld%lld", &pts[i].x, &pts[i].y);
        ll tmp = 0;
        rep(i,0,N-1) {
            int j = (i+1) % N;
            tmp = acc_area[i] = tmp + (pts[i].x + pts[j].x) * (pts[j].y - pts[i].y);
        }
        ll tot_area = tmp;
        ll ans = 0;
        rep(i,0,N-1) {
            int j1 = i+2;
            int j2 = i+N-2;
            while (j1 < j2) {
                int m = (j1 + j2) >> 1;
                if (predicate(tot_area,i,m % N)) {
                    j2 = m;
                } else {
                    j1 = m+1;
                }
            }
            tmp = get_area(i,j1%N);
            ans = max(ans, max(tmp, tot_area - tmp));
        }
        printf("%lld %lld\n", ans, tot_area - ans);
    }
    return 0;
}