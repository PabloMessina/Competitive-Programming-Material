#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ii> vii;

typedef vector<vi> graph;
typedef vector<vll> vvll;
typedef vector<vii> wgraph;

#define rep(i, n) for (int i = 0; i < n; i++)
#define repx(i, a, b) for (int i = a; i < (int)b; i++)
#define invrep(i, a, b) for (int i = b; i-- > (int)a;)

#define eb emplace_back

#define debugx(x) cerr << #x << ": " << x << endl
#define debugv(v)         \
    cerr << #v << ": ";   \
    for (auto e : v)      \
        cerr << e << " "; \
    cerr << endl
#define debugm(m)             \
    cerr << #m << ":\n";      \
    for (auto &v : m)         \
    {                         \
        for (auto e : v)      \
            cerr << e << " "; \
        cerr << "\n";         \
    }                         \
    cerr << endl

template <typename _Ty1, typename _Ty2>
std::ostream &operator<<(std::ostream &_os, const std::pair<_Ty1, _Ty2> &_p)
{
    _os << '(' << _p.first << ',' << _p.second << ')';
    return _os;
}

vector<vector<ll>> DP;

ll func(int n, int k)
{
    if (n < 0)
        return 0;
    if (k <= 0 and n > 0)
        return 0;
    if (n == 0)
        return 1;
    if (DP[n][k] != -1)
        return DP[n][k];

    return DP[n][k] = func(n, k - 1) + func(n - k, k - 1);
}

// ll func(int n, int k) {
// 	ll& ans = DP[n][k];
// 	if (ans != -1) return ans;
// 	if (n == 0) return ans = 1;
//     int tmp = k * (k+1) / 2;
// 	if (tmp < n) return ans = 0;
//     if (tmp == n) return ans = 1;
// 	if (k <= n) {
// 		ans = func(n - k, k - 1) + func(n, k-1);
// 	} else {
// 		ans = func(n, n);
// 	}
// 	return ans;
// }

int main()
{
    int n;
    cin >> n;
    DP.assign(n + 1, vector<ll>(n + 1, -1));

    cout << func(n, n-1) << '\n';
    //debugm(DP);
}