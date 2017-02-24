#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,c,s;
    int curr, count;
    while (scanf("%d%d%d",&n,&c,&s)==3) {
        s--;
        curr = 0;
        count = 0;
        if (curr == s) count++;
        while (c--) {
            int x; scanf("%d", &x);
            curr = (curr + x + n) % n;
            if (curr == s) count++;
        }        
        printf("%d\n", count);
    }
    return 0;
}