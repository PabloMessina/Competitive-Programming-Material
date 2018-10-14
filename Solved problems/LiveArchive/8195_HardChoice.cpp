#include <bits/stdc++.h>
using namespace std;
int main() {
    int ca, ba, pa, cr, br, pr;
    while (cin >> ca >> ba >> pa >> cr >> br >> pr) {
        cout << max(cr - ca, 0) + max(br - ba, 0) + max(pr - pa, 0) << endl;
    }
    return 0;
}