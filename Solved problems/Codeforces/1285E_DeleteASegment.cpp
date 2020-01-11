// tags: implementation, sortings, difference array
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
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    vector<int> A, C;
    A.reserve(1000000);
    C.reserve(1000000);
    while (t--) {
        int n; cin >> n;
        vector<pair<int,int>> segs(n);
        set<int> coords;
        for (auto& s : segs) {
            cin >> s.first >> s.second;
            coords.insert(s.first);
            coords.insert(s.second);
        }
        {
            int idx = 0;
            umap<int,int> x2i;
            for (int x : coords) {
                x2i[x] = idx++;
            }
            for (auto& s : segs) {
                s.first = x2i[s.first];
                s.second = x2i[s.second];
            }
        }
        A.assign(coords.size() * 2 + 5, 0);
        C.assign(coords.size() * 2 + 5, 0);
        int r = -1;
        int count = 0;
        sort(segs.begin(), segs.end());
        for (auto& s : segs) {
            if (s.first > r) count++;
            r = max(r, s.second);
            A[s.first * 2 + 1]++;
            A[s.second * 2 + (s.first == s.second) + 1]--;
        }
        int sum = 0;
        for (int& x : A) x = sum += x;
        rep (i, 1, C.size()) {
            if (A[i] == 1 and A[i-1] != 1) C[i]++;
            C[i] += C[i-1];
        }
        int ans = 0;
        for (auto& s : segs) {
            int i = s.first * 2 + 1;
            int j = s.second * 2 + (s.first == s.second) + 1;
            int d = C[j-1] - C[i-1] + (A[i] == 1 and A[i-1] == 1);
            if (A[i] == 1 and A[i-1] == 0) d--;
            if (A[j-1] == 1 and A[j] == 0) d--;
            ans = max(ans, count + d);
        }
        cout << ans << '\n';
    }
    return 0;
}