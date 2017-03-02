#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define invrep(i,a,b) for(int i=a; i>=b; i--)
int n,m;
int b, d_prev, d_after;
int C[5] = {1,10,100,1000,10000};
int main() {
    while (scanf("%d%d",&n,&m) == 2) {
        d_prev = d_after = 0;
        rep(i,1,m) {
            int tot = 0, tmp, dmove;
            scanf("%d %d", &b, &dmove);
            rep(j,2,n) { scanf("%d", &tmp); tot += tmp; }
            if (dmove + tot <= b)
                d_prev += dmove;
            invrep(j,4,0) {
                if (C[j] + tot <= b) {
                    d_after += C[j];
                    break;
                }
            }
        }
        printf("%d\n",d_after-d_prev);
    }
    return 0;
}