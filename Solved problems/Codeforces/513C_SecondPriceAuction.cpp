// tags: bitwise, brute force, backtracking, probabilities
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
int n;
ll L[5], R[5];
vector<int> groups[3]; // 3 groups
bool used[5];
ll b;
ll sum = 0;

void search(int g) {
    vector<int> &group = groups[g];
    if (g == 0) { // group 0 -> above b
        // case 1: empty
        search(1);
        // case 2: 1
        for (int i = 0; i < n; ++i) {
            if (b >= R[i]) continue; // not possible
            used[i] = true;
            group.push_back(i);
            search(1);
            used[i] = false;
            group.pop_back();
        }
    } else if(g == 1) { // group 1 -> exactly b
        vector<int> available;
        rep(i,0,n) if (!used[i]) available.push_back(i);
        int min_size = groups[0].empty() ? 2 : 1; // at least 1
        int max_size = available.size();
        if (max_size < min_size) return;
        for (int mask=0; mask < (1 << max_size); ++mask) {
            if (__builtin_popcount(mask) < min_size) continue;
            int size = 0;
            for (int i = 0; i < max_size; ++i) {
                if (mask & (1 << i)) {
                    used[available[i]] = true;
                    group.push_back(available[i]);
                    ++size;
                }
            }
            search(2); // search for groups[2]
            for (int i = 0; i < max_size; ++i) {
                if (mask & (1 << i)) {
                    used[available[i]] = false;
                    group.pop_back();
                }
            }
        }
    } else { // group 2 -> below b (all remaining)
        ll ways = 1;
        // group 0 -> above b
        for (int i : groups[0]) ways *= max(0LL, R[i] - max(b + 1, L[i]) + 1);
        // group 1 -> exactly b
        for (int i : groups[1]) ways *= max(0LL, min(R[i], b) - max(L[i], b) + 1);
        // group 2 -> below b
        rep(i,0,n) if (!used[i]) ways *= max(0LL, min(b-1, R[i]) - L[i] + 1);
        sum += ways;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    ll min_b = LLONG_MAX;
    ll max_b = LLONG_MIN;
    rep(i,0,n) {
        cin >> L[i] >> R[i];
        min_b = min(min_b, L[i]);
        max_b = max(max_b, R[i]);
    }
    double ans = 0;
    for (b = min_b; b <= max_b; ++b) {
        sum = 0;
        search(0);
        double p = sum;
        rep(i,0,n) p /= (R[i] - L[i] + 1);
        ans += p * b;
    }
    cout << fixed << setprecision(20) << ans << '\n';
    return 0;
}