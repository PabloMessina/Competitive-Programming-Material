// tags: greedy
#include <bits/stdc++.h>
using namespace std;
int main() {
    string s; cin >> s;
    int i = 0;
    while (i < s.size() and s[i] == 'a') ++i;
    if (i == s.size()) s.back() = 'z';
    else while (i < s.size() and s[i] != 'a') s[i++]--;
    cout << s << '\n';
    return 0;
}