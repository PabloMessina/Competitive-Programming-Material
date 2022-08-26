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
int main() {
    // ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(k,1,T+1) {
        string query = "00000000";
        cout << query << '\n';
        int feedback;
        cin >> feedback;
        while (feedback != -1 and feedback != 0) {
            int n_ones = feedback;
            query = "00000000";
            rep(i,0,n_ones) query[i] = '1';
            cout << query << '\n';
            cin >> feedback;
        }
    }
    return 0;
}