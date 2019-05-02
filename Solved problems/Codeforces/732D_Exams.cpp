// tags: binary search, greedy
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,a,b) for(int i = a; i >= b; --i)

const int MAXN = 100000;
int N,M;
int exams[MAXN];
int days[MAXN+1];

bool possible(int d) {
    static bool passed[MAXN+1];
    static bool islast[MAXN];
    memset(passed, 0, sizeof(bool) * (M+1));
    memset(islast, 0, sizeof(bool) * (d+1));
    invrep(i,d,0) {
        if (exams[i] != 0 and !passed[exams[i]]) {
            passed[exams[i]] = true;
            islast[i] = true;
        }
    }
    int count = 0;
    int pending = M;
    rep(i,0,d) {
        if (islast[i]) {
            if (count < days[exams[i]]) return false;
            count -= days[exams[i]];
            pending--;
        } else {
            count++;
        }
    }
    return pending == 0;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> N >> M;
    rep(i,0,N-1) cin >> exams[i];
    rep(i,1,M) cin >> days[i];
    int l = 0, r = N;
    while (l < r) {
        int m = (l+r) >> 1;
        if (possible(m)) r = m;
        else l = m+1;
    }
    if (l == N) cout << -1 << '\n';
    else cout << (l+1) << '\n';
    return 0;
}