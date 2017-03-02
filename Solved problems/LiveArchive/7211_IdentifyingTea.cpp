#include <bits/stdc++.h>
using namespace std;
int main() {
    int t,a,b,c,d,e;
    while(scanf("%d%d%d%d%d%d",&t,&a,&b,&c,&d,&e) == 6) {
        printf("%d\n",(a==t)+(b==t)+(c==t)+(d==t)+(e==t));
    }
    return 0;
}