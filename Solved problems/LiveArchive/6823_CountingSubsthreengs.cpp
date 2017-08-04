// modular aritmetics, combinatorics
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef long long int ll;

// check if a char is a digit
bool is_digit(char c) { return '0' <= c && c <= '9'; }

int main() {
    string line;
    while (getline(cin,line)) { // for each input line
        int n = line.size();
        ll threes = 0; // count number of threes
        rep(i,0,n-1) {
            if (is_digit(line[i])) { // starting a substring of digits

                // find the rightmost position of the island of digits
                int j = i;
                while (j+1 < n && is_digit(line[j+1])) j++;
                
                int sum = 0; // keep track of accumulated sums mod 3
                ll c[3] = {0,0,0}; // count how many times each sum mode 3 (0,1,2) appears
                rep(k,i,j) {
                    sum = (sum + (line[k] - '0')) % 3; // update sum mode 3
                    c[sum]++; // add to count
                }
                // all pairs between 1's, all pairs between 2's
                // all pairs between 0's and all 0's define numbers multiple of 3
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