// tags: greedy
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

int main() {
    string line;
    int counts[10];
    vector<int> digits;
    int len, start;
    while(getline(cin,line)) {
        memset(counts, 0, sizeof counts);
        digits.clear();
        len = line.size();
        start = len;
        rep(i,0,len-1) {
            int d = line[i] - '0';            
            digits.push_back(d);
            if (++counts[d] > 2) {
                while (true) {
                    bool stop = false;
                    d = line[i] - '0';
                    counts[d]--;
                    digits.pop_back();
                    invrep(k, d-1, 0) {
                        if (counts[k] < 2) {
                            digits.push_back(k);
                            counts[k]++;
                            stop = true;
                            break;
                        }
                    }
                    if (stop) break;
                    i--;
                }
                start = i + 1;
                break;
            }
        }        
        rep(i,start,len-1) {
            invrep(d,9,0) {
                if (counts[d] < 2) {
                    digits.push_back(d);
                    counts[d]++;
                    break;
                }
            }
        }
        if (digits[0] != 0) printf("%d", digits[0]);
        rep(i,1,len-1) printf("%d", digits[i]);
        puts("");
    }
    return 0;
}