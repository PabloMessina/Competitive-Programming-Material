// tags: ad-hoc, greedy, implementation
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

int N, A[3], B[3];
char imp[] = "IMPOSSIBLE";
char cols[] = "RYBGVO";

void print_color(int c, bool seen[]) {
    putchar(cols[c]);
    if (!seen[c]) {
        seen[c] = true;
        rep(i,1,B[c]) {
            putchar(cols[c+3]);
            putchar(cols[c]);
        }
    }
}

void solve() {
    rep(i,0,2) {
        if (B[i] > 0 and ((A[i] + B[i] == N and A[i] != B[i]) or (A[i] + B[i] != N and A[i] <= B[i]))) {
            puts(imp);
            return;
        }
    }
    rep(i,0,2) {
        if (A[i] + B[i] == N and A[i] == B[i]) {
            rep(j, 1, A[i]) {
                putchar(cols[i]);
                putchar(cols[i+3]);
            }
            puts("");
            return;
        }
    }
    
    ii v[3];
    rep(i,0,2) v[i] = {A[i] - B[i], i};
    sort(v, v + 3);
    
    if (v[2].first > v[1].first + v[0].first) {
        puts(imp);
        return;
    }

    bool seen[3] = {0};
    int extra = v[1].first + v[0].first - v[2].first;
    if (extra) {
        rep(i,1,extra+1) {
            int c = v[i%2].second;
            v[i%2].first--;
            print_color(c, seen);
        }
        print_color(v[2].second, seen);
    }
    rep(i,0,1) {
        while (v[i].first--) {
            print_color(v[i].second, seen);
            print_color(v[2].second, seen);
        }
    }
    puts("");
}

int main() {
    int T; scanf("%d", &T);
    rep(_case, 1, T) {
        scanf("%d",&N);
        rep(i,0,2) {
            scanf("%d", &A[i]);
            scanf("%d", &B[(i+2)%3]);
        }
        printf("Case #%d: ", _case);
        solve();
    }
    return 0;
}