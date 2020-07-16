#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
void validate(vector<int>& next_, vector<int>& prev_, vector<tuple<ll,ll,int>>& scores, set<tuple<ll,ll,int>>& s, vector<ll>& a, int n) {
    for (auto& it : s) {
        ll x, y; int i; tie(x,y,i) = it;
        x = -x;
        assert (x >= 0);
        assert (y >= 0);
        assert (0 <= i and i < n);
        assert (scores[i] == it);
        assert (a[i] == x);
        assert (y == a[next_[i]] + a[prev_[i]]);
        assert (next_[prev_[i]] == i);
        assert (prev_[next_[i]] == i);
    }
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n; cin >> n;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;
    vector<int> next_(n), prev_(n);
    vector<tuple<ll,ll,int>> scores(n);
    set<tuple<ll,ll,int>> s;
    auto get_tuple = [&next_, &prev_, &a](int i) {
        return make_tuple(-a[i], a[next_[i]] + a[prev_[i]], i);
    };
    rep(i,0,n) {
        next_[i] = (i+1) % n;
        prev_[i] = (i-1+n) % n;
        scores[i] = get_tuple(i);
        s.insert(scores[i]);
    }    
    // validate(next_, prev_, scores, s, a, n);
    while (s.size() > 1) {
        ll aa = get<1>(*s.rbegin());
        int i = get<2>(*s.rbegin());
        // assert (get<0>(*s.rbegin()) == -a[i]);
        // assert (aa == a[prev_[i]] + a[next_[i]]);
        // assert (s.size() % 2 == 1);
        // printf("i = %d, aa = %lld, s.size()=%d\n", i, aa, s.size());
        a[i] = aa;
        s.erase(scores[i]);
        s.erase(scores[prev_[i]]);
        s.erase(scores[next_[i]]);
        // puts("debug0");
        // validate(next_, prev_, scores, s, a, n);
        if (s.size() >= 2) {
            prev_[i] = prev_[prev_[i]];
            next_[i] = next_[next_[i]];
            s.erase(scores[prev_[i]]);
            s.erase(scores[next_[i]]);
            next_[prev_[i]] = i;
            prev_[next_[i]] = i;
            scores[prev_[i]] = get_tuple(prev_[i]);
            scores[next_[i]] = get_tuple(next_[i]);
            s.insert(scores[prev_[i]]);
            s.insert(scores[next_[i]]);
            // puts("debug1");
            // validate(next_, prev_, scores, s, a, n);            
        }        
        scores[i] = get_tuple(i);
        s.insert(scores[i]);
        // puts("debug2");
        // validate(next_, prev_, scores, s, a, n);
    }
    // assert (s.size() == 1);
    cout << -get<0>(*s.begin()) << '\n';
    return 0;
}