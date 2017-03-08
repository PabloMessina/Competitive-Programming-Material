// modular aritmetics, combinatorics
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef long long int ll;
bool is_digit(char c) { return '0' <= c && c <= '9'; }
int main() {
    string line;    
    while (getline(cin,line)) {
        int n = line.size();        
        ll threes = 0;
        rep(i,0,n-1) {
            if (is_digit(line[i])) {
                int j = i;
                while (j+1 < n && is_digit(line[j+1])) j++;
                int sum = 0;
                ll c[3] = {0,0,0};
                rep(k,i,j) {
                    sum = (sum + (line[k] - '0')) % 3;
                    c[sum]++;
                }
                threes += c[0] + c[0] * (c[0]-1) / 2;
                threes += c[1] * (c[1]-1) / 2;
                threes += c[2] * (c[2]-1) / 2;
                i = j;
            }
        }
        printf("%lld\n", threes);
    }
    return 0;
}