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
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n; cin >> n;
    vector<int> count(n + 1, 0);
	rep(i,2,n+1)
		if (count[i] == 0)
			for (int j = i; j <= n; j += i)
				count[j]++;    	
	int ans = 0;
    rep(i,2,n+1) if (count[i] == 2) ans++;
    cout << ans << '\n';
    return 0;
}