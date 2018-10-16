// TODO: fix this
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

const int MAXN = 100000 + 1;
int N;
ll MOD = 1000000000 + 7;

struct Gate {
    int x, y, f;
} gates[MAXN];

ll inline add(ll x, ll y) { return (x+y)%MOD; }
ll inline mul(ll x, ll y) { return (x*y)%MOD; }

ll incorrect(int i, int b);

ll correct_memo[MAXN][2];
ll correct(int i, int b) {
    // printf("correct:: i=%d, b=%d\n", i, b);
    ll& ans = correct_memo[i][b];
    if (ans != -1) return ans;
    if (i == 0) return ans = 1;    
    Gate& g = gates[i];
    ll tmp = 0;
    if (g.f == -1) { // normal
        if (b == 0) { // correct-0
            tmp = add(tmp, mul(correct(g.x, 1), correct(g.y, 1)));
        } else { // correct-1
            assert (b == 1);
            // C0 vs all
            tmp = add(tmp, mul(correct(g.x, 0), correct(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 0), correct(g.y, 1)));
            tmp = add(tmp, mul(correct(g.x, 0), incorrect(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 0), incorrect(g.y, 1)));
            // C1,I0,I1 vs C0
            tmp = add(tmp, mul(correct(g.x, 1), correct(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 0), correct(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 1), correct(g.y, 0)));
        }
    } else if (g.f == 0) { // stuck 0
        if (b == 0) { // correct-0
            tmp = add(tmp, mul(correct(g.x, 1), correct(g.y, 1)));
            tmp = add(tmp, mul(correct(g.x, 1), incorrect(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 0), correct(g.y, 1)));
            tmp = add(tmp, mul(incorrect(g.x, 0), incorrect(g.y, 0)));
        } else { // correct-1
            assert (b == 1);
            tmp = 0;
        }
    } else { // stuck 1
        assert (g.f == 1);
        if (b == 0) { // correct-0
            tmp = 0;
        } else { // correct-1
            assert (b == 1);
            // C0 vs all
            tmp = add(tmp, mul(correct(g.x, 0), correct(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 0), correct(g.y, 1)));
            tmp = add(tmp, mul(correct(g.x, 0), incorrect(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 0), incorrect(g.y, 1)));
            // I1 vs all
            tmp = add(tmp, mul(incorrect(g.x, 1), correct(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 1), correct(g.y, 1)));
            tmp = add(tmp, mul(incorrect(g.x, 1), incorrect(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 1), incorrect(g.y, 1)));
            // C1 vs C0,I1
            tmp = add(tmp, mul(correct(g.x, 1), correct(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 1), incorrect(g.y, 1)));
            // I0 vs C0,I1
            tmp = add(tmp, mul(incorrect(g.x, 0), correct(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 0), incorrect(g.y, 1)));
        }
    }
    return ans = tmp;
}

ll incorrect_memo[MAXN][2];
ll incorrect(int i, int b) {
    // printf("incorrect:: i=%d, b=%d\n", i, b);
    ll& ans = incorrect_memo[i][b];
    if (ans != -1) return ans;
    if (i == 0) return ans = 0;
    Gate& g = gates[i];
    ll tmp = 0;
    if (g.f == -1) { // normal
        if (b == 0) { // incorrect-0        
            tmp = add(tmp, mul(incorrect(g.x, 1), incorrect(g.y, 1)));
            tmp = add(tmp, mul(incorrect(g.x, 1), correct(g.y, 1)));
            tmp = add(tmp, mul(correct(g.x, 1), incorrect(g.y, 1)));
        } else { // incorrect-1
            assert (b == 1);
            // I0 vs C1,I0,I1
            tmp = add(tmp, mul(incorrect(g.x, 0), correct(g.y, 1)));
            tmp = add(tmp, mul(incorrect(g.x, 0), incorrect(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 0), incorrect(g.y, 1)));
            // C1,I1 vs I0
            tmp = add(tmp, mul(correct(g.x, 1), incorrect(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 1), incorrect(g.y, 0)));
        }
    } else if (g.f == 0) { // stuck 0
        if (b == 0) { // incorrect-0
            // C0 vs all
            tmp = add(tmp, mul(correct(g.x, 0), correct(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 0), correct(g.y, 1)));
            tmp = add(tmp, mul(correct(g.x, 0), incorrect(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 0), incorrect(g.y, 1)));
            // I1 vs all
            tmp = add(tmp, mul(incorrect(g.x, 1), correct(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 1), correct(g.y, 1)));
            tmp = add(tmp, mul(incorrect(g.x, 1), incorrect(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 1), incorrect(g.y, 1)));            
            // C1 vs C0,I1
            tmp = add(tmp, mul(correct(g.x, 1), correct(g.y, 0)));
            tmp = add(tmp, mul(correct(g.x, 1), incorrect(g.y, 1)));
            // I0 vs C0,I1
            tmp = add(tmp, mul(incorrect(g.x, 0), correct(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 0), incorrect(g.y, 1)));
        } else { // incorrect-1
            assert (b == 1);
            tmp = 0;
        }
    } else { // stuck 1
        assert (g.f == 1);
        if (b == 0) { // incorrect-0
            tmp = 0;
        } else { // incorrect-1
            assert (b == 1);
            tmp = add(tmp, mul(correct(g.x, 1), correct(g.y, 1)));
            tmp = add(tmp, mul(correct(g.x, 1), incorrect(g.y, 0)));
            tmp = add(tmp, mul(incorrect(g.x, 0), correct(g.y, 1)));
            tmp = add(tmp, mul(incorrect(g.x, 0), incorrect(g.y, 0)));
        }
    }
    return ans = tmp;
}

int main() {
    while (cin >> N) {
        rep(i,1,N) {
            Gate& g = gates[i];
            cin >> g.x >> g.y >> g.f;
        }
        memset(correct_memo, -1, sizeof(correct_memo));
        memset(incorrect_memo, -1, sizeof(incorrect_memo));
        cout << add(incorrect(1,0), incorrect(1,1)) << endl;
    }
    return 0;
}