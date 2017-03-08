// tags: greedy
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int main() {
    ll a,b;
    string line;
    while (scanf("%lld%lld\n",&a,&b)==2) {
        getline(cin,line);
        int n = line.size();
        int i = 0, j = n - 1;
        ll cost = 0;
        while (true) {
            while (i < n and line[i] == 'B') i++;
            while (j >= 0 and line[j] == 'W') j--;
            if (i >= j) break;
            cost += min(a, (a-b) * (j-i));
            i++, j--;
        }
        printf("%lld\n", cost);
    }
    return 0;
}