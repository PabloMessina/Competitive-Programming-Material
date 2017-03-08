#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
int main() {
    int x[5], y[5];
    while (scanf("%d",&x[0]) == 1) {
        rep(i,1,4) scanf("%d",&x[i]);
        rep(i,0,4) scanf("%d",&y[i]);
        bool comp = true;
        rep(i,0,4) if (x[i] == y[i]) { comp = false; break; }
        if (comp) puts("Y");
        else puts("N");
    }
    return 0;
}