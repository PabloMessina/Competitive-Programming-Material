// TODO: finish this
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------
typedef long long int128_t;
typedef unsigned long long uint128_t;

uint128_t in() {
    string s; cin >> s;
    uint128_t x = 0;
    for (char c : s) x = x * 10 + (c-'0');
    return x;
}

out(uint128_t x) {
    static int digits[128];
    int i = 0;
    while(x) { digits[i++] = x%10; x/=10; }
    invrep(j,i-1,0) cout << digits[j];
}

int main() {
    // OPTIONAL: for faster input/output (only if using cin/cout)
    ios::sync_with_stdio(false); 
    cin.tie(0);
    uint128_t x = in();
    cout << "rofl "; out(x);
    return 0;
}