// tags: implementation, std::set
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int N;
int freq[100001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    set<pair<int,int>> s;
    cin >> N;
    int max_x = -1;
    rep(x,1,N) {
        int u; cin >> u;
        auto it = s.find({freq[u], u});
        if (it != s.end()) s.erase(it);
        freq[u]++;
        s.emplace(freq[u], u);
        if ((s.size() == 1) or
            ((s.rbegin()->first == s.begin()->first + 1) and
                (s.rbegin()->first == next(s.rbegin())->first + 1)) or
            ((s.begin()->first == 1) and
                (next(s.begin())->first == s.rbegin()->first))
        ) max_x = x;
    }
    cout << max_x << '\n';
    return 0;
}