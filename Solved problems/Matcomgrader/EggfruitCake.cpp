// tags: implementation, two pointers
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    string B; int S;
    cin >> B >> S;
    int N = B.size();
    ll count = 0;
    int j = 0;
    rep(i,0,N) {
        if (j < i) j = i;
        while (B[j%N] != 'E' and j - i + 1 < S) ++j;
        if (B[j%N] == 'E') count += S - (j-i);
    }
    cout << count << '\n';
    return 0;
}