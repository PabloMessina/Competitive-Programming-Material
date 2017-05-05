/* ========= */
// Template  //
/* ========= */
#include <bits/stdc++.h> // add almost everything in one shot
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

int main() {
    int T; scanf("%d", &T);
    rep(_case,1,T) {
        double D; int N;
        scanf("%lf%d", &D, &N);
        double max_t = -1.0;
        while(N--) {
            double K,S;
            scanf("%lf%lf", &K, &S);
            max_t = max(max_t, (D - K) / S);
        }
        printf("Case #%d: %lf\n", _case, D / max_t);
    }
    return 0;
}