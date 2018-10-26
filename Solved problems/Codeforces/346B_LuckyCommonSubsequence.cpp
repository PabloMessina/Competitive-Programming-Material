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

string s1, s2, virus;
int n1, n2, nv;

int memo_lcs[100][100][100];
iii memo_next[100][100][100];

int dp(int i, int j, int k) {
    if (k == nv) return -1;
    if (i == n1) return 0;
    if (j == n2) return 0;
    int& ans = memo_lcs[i][j][k];
    if (ans != -1) return ans;
    int tmp;

    iii& nxt = memo_next[i][j][k];

    if (s1[i] == s2[j]) {
        int kk = s1[i] == virus[k] ? k + 1 : k;
        tmp = dp(i+1, j+1, kk);
        if (tmp != -1 and tmp + 1 > ans) {
            ans = tmp + 1;
            bnxt = iii(i+1, j+1, kk);
        }
    }

    tmp = dp(i+1, j, k);
    if (tmp != -1 and tmp + 1 > ans) {
        ans = tmp + 1;        
        bnxt = iii(i+1, j, k);
    }

    tmp = dp(i, j+1, k);
    if (tmp != -1 and tmp + 1 > ans) {
        ans = tmp + 1;        
        bnxt = iii(i, j+1, k);
    }

    if (ans == -1) {
        bnxt = iii(-1, -1, -1);
    }

    return ans;
}

int main() {
    cin >> s1 >> s2 >> virus;
    n1 = s1.size();
    n2 = s2.size();
    nv = virus.size();
    memset(memo_lcs, -1, sizeof memo_lcs);
    printf("s1 = %s\n", s1.c_str());
    printf("s2 = %s\n", s2.c_str());
    printf("virus = %s\n", virus.c_str());
    printf("n1=%d, n2=%d, nv=%d\n", n1, n2, nv);
    int ans = dp(0,0,0);
    cout << ans << endl;
    return 0;
}