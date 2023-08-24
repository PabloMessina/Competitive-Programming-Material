// TODO: Fix this (WA)
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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N, X;
vi T;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> X;
    int ans = 0;
    rep(i,0,N) {
        int t; cin >> t;
        if (t < X) {
            T.pb(t);
        } else {
            ans = max(ans, t);
        }
    }
    if (T.size() <= 2) {
        ans = max(ans, T.back());
        cout << ans << '\n';
        return 0;
    }
    sort(T.begin(), T.end());
    multiset<ii> state;
    state.insert({0, T[0]}); // (start, duration)
    state.insert({0, T[1]}); // (start, duration)
    int start_time = 0;
    int end_time = max(T[0], T[1]);
    int lb = X + 1; // lower bound for the next duration
    invrep(i, T.size() - 1, 2) {
        int d = T[i];
        assert (state.size() > 0);
        int e, s;
        if (state.size() == 1) {
            auto it = state.begin();
            int s1 = it->ff, d1 = it->ss; ++it;
            e = lb, s = e - d;
            lb = max(lb, min(s1, s) + X + 1);
        } else if (state.size() == 2) {
            auto it = state.begin();
            int s1 = it->ff, d1 = it->ss; ++it;
            int s2 = it->ff, d2 = it->ss;
            assert (lb >= s1 + X + 1);
            e = lb, s = e - d;
            state.erase(state.begin());
            if (s1 == s2) {
                state.erase(state.begin());
                assert (state.size() == 0);
            } else {
                assert (state.size() == 1);
                lb = max(lb, min(s2, s) + X + 1);
            }
        } else {
            assert(false);
        }
        state.insert({s, d});
        start_time = min(start_time, s);
        end_time = max(end_time, e);
    }
    assert (start_time < end_time);
    ans = max(ans, end_time - start_time);
    cout << ans << '\n';
    return 0;
}