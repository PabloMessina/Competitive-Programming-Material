// tags: interactive, implementation, strings
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
int in() {
    int x; cin >> x;
    if (x == 0) exit(0);
    return x;
}
void out(const string& s) {
    cout << s << '\n';
    cout.flush();
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    string onlyA(300,'a');
    out(onlyA);
    int na = 300 - in();
    string onlyB(300,'b');
    out(onlyB);
    int nb = 300 - in();
    string ans;
    if (na == 0) {
        ans = string(nb,'b');
        out(ans); in();
        assert(false);
    }
    if (nb == 0) {
        ans = string(na,'a');
        out(ans); in();
        assert(false);
    }
    int n = na + nb;
    ans = string(n,'a');
    int i = 0;
    rep(k,1,nb+1) {
        int expected = nb - k;
        while (1) {
            ans[i] = 'b';
            out(ans);
            if (in() != expected) {
                ans[i++] = 'a';
            } else {
                ++i; break;
            }
        }
    }
    return 0;
}