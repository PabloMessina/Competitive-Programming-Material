// tags: implementation, sorting, two pointers
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int hard[200000];
ll times[200000];
int indexes[200000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int m; cin >> m;
    while (m--) {
        int n; ll T, a, b;
        cin >> n >> T >> a >> b;
        int tot_easy = 0;
        int tot_hard = 0;
        rep(i,0,n) {
            cin >> hard[i];
            if (hard[i]) tot_hard++;
            else tot_easy++;
        }
        set<ll> leave_times;
        rep(i,0,n) {
            cin >> times[i];
            leave_times.insert(times[i]);
            if (times[i] > 0) leave_times.insert(times[i] - 1);
        }
        leave_times.insert(T);
        rep(i,0,n) indexes[i] = i;
        sort(indexes, indexes+n, [](int i, int j) { return times[i] < times[j]; });
        int i = 0;
        ll acct = 0;
        int hard_count = 0;
        int easy_count = 0;
        int ans = 0;
        for (auto& t : leave_times) {
            while (i < n and times[indexes[i]] <= t) {
                int j = indexes[i];
                if (hard[j]) {
                    acct += b;
                    hard_count++;
                } else {
                    acct += a;
                    easy_count++;
                }
                ++i;
            }
            if (acct <= t) {
                int count = hard_count + easy_count;
                ll r = t - acct;
                if (r > 0) {
                    int extra_easy = min(tot_easy - easy_count, (int)(r/a));
                    r -= extra_easy * a;
                    count += extra_easy;
                }
                if (r > 0) {
                    int extra_hard = min(tot_hard - hard_count, (int)(r/b));
                    r -= extra_hard * b;
                    count += extra_hard;
                }
                ans = max(ans, count);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}