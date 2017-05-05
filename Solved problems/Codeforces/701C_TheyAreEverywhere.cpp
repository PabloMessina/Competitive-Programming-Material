// tags: two pointers
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;

const int MAXN = 100000;
int acc[MAXN][52];
int n;
set<int> used;

int char2int(char c) {
    if ('a' <= c and c <= 'z') return c - 'a';
    return 26 + (c - 'A');
}

bool valid_range(int i, int j) {
    for(int x : used) {
        int delta = acc[j][x] - (i > 0 ? acc[i-1][x] : 0);
        if (delta == 0) return false;
    }
    return true;
}

int main() {
    scanf("%d\n", &n);    
    rep(i,0,n-1) {
        int x = char2int(getchar());
        used.insert(x);
        if (i > 0) rep(j,0,51) acc[i][j] = acc[i-1][j];
        else rep(j,0,51) acc[i][j] = 0;
        acc[i][x]++;
    }
    int i = 0, j = 0;
    int min_range = INT_MAX;
    while (j < n) {
        if (valid_range(i,j)) {
            min_range = min(min_range, j-i+1);
            i++;
            if (j < i) j++;
        } else {
            j++;
        }
    }
    printf("%d\n", min_range);
    return 0;
}