// tags: implementation
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

typedef vector<int> vi;
typedef pair<int,int> pii;

char buff[201];
bool ignored[201];

int main() {
    string exp;
    getline(cin, exp);

    stack<int> indexes;
    vector<pii> brackets;

    rep(i,0,exp.size()-1) {
        if (exp[i] == '(') {
            indexes.push(i);
        } else if (exp[i] == ')') {
            brackets.push_back({indexes.top(), i});
            indexes.pop();
        }
    }

    set<string> combs;
    memset(ignored, 0, sizeof ignored);

    int n = brackets.size();
    int times = (1 << n) - 1;
    vector<int> within(n, 0);
    while (times--) {
        // set chars to ignore
        rep(i,0,n-1) {
            pii b = brackets[i];
            if (within[i]) {
                ignored[b.first] = false;
                ignored[b.second] = false;
            } else {
                ignored[b.first] = true;
                ignored[b.second] = true;
            }
        }
        // generate and record comb
        int i = 0;
        rep (j,0,exp.size()-1) {
            if (ignored[j]) continue;
            buff[i++] = exp[j];
        }
        buff[i] = '\0';
        string comb(buff);
        combs.insert(comb);
        // next comb
        int carry = 1;
        rep(i,0,n-1) {
            within[i] += carry;
            if (within[i] <= 1)
                break;
            within[i] = 0;
        }
    }

    // print all combs
    for (auto& comb : combs) {
        printf("%s\n", comb.c_str());
    }

    return 0;
}