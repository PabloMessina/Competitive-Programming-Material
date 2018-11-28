// tags: implementation, math
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i <= b; ++i)
typedef long long int ll;

int inline char2digit(char c) {
    if ('0' <= c and c <= '9') return c - '0';
    return 10 + c - 'a';
}

ll getval(string& s, int b) {
    ll val = 0;
    for (char c : s) {
        val = val * b + char2digit(c);
    }
    return val;
}

bool valid_equation(ll x1, ll x2, ll y, char op) {
    if (op == '+') return x1 + x2 == y;
    if (op == '-') return x1 - x2 == y;
    if (op == '*') return x1 * x2 == y;
    assert (op == '/');
    return x1 % x2 == 0 and x1 / x2 == y;
}

string bases = "_123456789abcdefghijklmnopqrstuvwxyz0";

int main() {
    int n; cin >> n;
    getchar(); // consume EOL
    while (n--) {
        string line; getline(cin, line);
        stringstream ss(line);
        string num1, num2, result; char op, eq;
        ss >> num1 >> op >> num2 >> eq >> result;
        bool only_ones  = true;
        int minb = 2;
        for (char c : num1) {
            if (c != '1') only_ones = false;
            minb = max(minb, char2digit(c) + 1);
        }
        for (char c : num2) {
            if (c != '1') only_ones = false;
            minb = max(minb, char2digit(c) + 1);
        }
        for (char c : result) {
            if (c != '1') only_ones = false;
            minb = max(minb, char2digit(c) + 1);
        }
        bool invalid = true;
        if (only_ones) {
            int x1 = num1.size();
            int x2 = num2.size();
            int y = result.size();
            if (valid_equation(x1,x2,y,op)) {
                invalid = false;
                cout << '1';
            }
        }
        rep(b,minb,36) {
            ll x1 = getval(num1, b);
            ll x2 = getval(num2, b);
            ll y = getval(result, b);
            if (valid_equation(x1,x2,y,op)) {
                invalid = false;
                cout << bases[b];
            }
        }
        if (invalid) cout << "invalid\n";
        else cout << '\n';
    }
    return 0;
}