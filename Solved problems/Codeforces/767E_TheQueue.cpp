// TODO: finish this
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
ll TS, TF, T;
int n;

int main() {
    scanf("%lld%lld%lld%d", &TS, &TF, &T, &n);
    if (n == 0) { puts("0"); return 0; }
    map<ll,int> counts;
    rep(i,0,n-1) {
        ll a; scanf("%lld", &a);
        auto it = counts.find(a);
        if (it == counts.end()) {
            counts[a] = 1;
        } else {
            it->second++;
        }
    }
    if (counts.size() == 1) { puts("0"); return 0; }
    
    // -------------
    ll tbest=-1, minwait = LLONG_MAX;    
    ll next_free_time = TS;

    for (auto& p : counts) {
        ll a = p.first;
        int count = p.second;
        if (next_free_time < a) {
            tbest = next_free_time;
            break;
        } else {
            if (a > 0) {
                ll t = a - 1;
                ll wait = next_free_time - t;                
                if (wait < minwait) {
                    minwait = wait;
                    tbest = t;
                }
            }
            next_free_time += count * T;
        }
    }
    if (next_free_time < TF) tbest = next_free_time;
    assert(tbest >= 0);
    printf("%lld\n", tbest);
    return 0;
}