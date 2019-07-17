// tags: math, bases, implementation
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;

int max_digit(string& s) {
    int d = 0;
    for (char c : s) d = max(d, c-'0');
    return d;
}

int parse_num(string& s, int base) {
    int x = 0;
    for (char c : s) x = x * base + (c - '0');
    return x;
}

int num_digits(int x, int base) {
    int count = 0;
    while (x > 0) {
        count++;
        x /= base;
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string a, b;
    cin >> a >> b;
    int base = max(max_digit(a), max_digit(b))+1;
    int sum = parse_num(a, base) + parse_num(b, base);
    cout << num_digits(sum, base) << '\n';
    return 0;
}