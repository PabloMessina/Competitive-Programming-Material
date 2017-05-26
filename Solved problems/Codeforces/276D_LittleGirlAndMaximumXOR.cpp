#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const ll ONE = 1;

int main() {
    ll left, right ; scanf("%I64d %I64d", &left, &right);
    int n = sizeof(right) * 8 - __builtin_clzll(right);
    int i = n-1;
    while (i >= 0 and ((left >> i) & 1) == ((right >> i)  & 1) ) i--;
    printf("%I64d\n", (ONE << (i+1))-1 );
    return 0;
}