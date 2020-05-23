// tags: divide and conquer
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
vector<vector<int>> teams;
void search(int l, int r, int i) {
    int m = (l+r) >> 1;
    if (teams.size() == i) teams.resize(i+1);
    rep(k,l,m) teams[i].push_back(k);
    if (m-l > 1) search(l,m,i+1);
    if (r-m > 1) search(m,r,i+1);
}
int main() {
    freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n; cin >> n;
    search(0,n,0);
    cout << teams.size() << '\n';
    for (auto& team : teams) {
        cout << team.size();
        for (int x : team) cout << ' ' << x+1;
        cout << '\n';
    }
    return 0;
}