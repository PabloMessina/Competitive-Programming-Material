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

void add_to_map(map<ll,ll>& dict, ll n, ll count) {
    auto it = dict.find(n);
    if (it == dict.end()) dict[n] = count;
    else it->second += count;
}

int main() {
    int T;
    ll N, K;
    scanf("%d", &T);
    rep(t,1,T) {
        scanf("%lld%lld",&N,&K);
        map<ll, ll> layers[2];
        int prev = 0, cur = 1;
        layers[cur][N] = 1;
        ll tot = 1;
        while (K > tot) {
            swap(prev,cur);
            layers[cur].clear();
            for (auto& it : layers[prev]) {
                ll n = it.first - 1;
                ll count = it.second;
                if (n > 1) {
                    tot += 2 * count;
                    add_to_map(layers[cur], n/2, count);
                    add_to_map(layers[cur], n - n/2, count);
                } else {
                    tot += count;
                    add_to_map(layers[cur], n, count);
                }
            }          
        }
        ll delta = tot - K;
        ll acc = 0;
        ll min_, max_;
        for (auto& it : layers[cur]) {
            acc += it.second;
            if (acc > delta) {
                ll n = it.first - 1;  
                min_ = min(n / 2, n - n/2);
                max_ = max(n / 2, n - n/2);
                break;
            }
        }
        printf("Case #%d: %lld %lld\n", t, max_, min_);
    }
    return 0;
}