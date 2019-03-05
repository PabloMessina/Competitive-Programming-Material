// tags: backtracking, pruning, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------

int total, n;
int values[12];
int counts[12];
int tmp_counts[12];

bool solve(int i, int accsum) {
    if (accsum > total) return false;
    if (i == n) {
        if (accsum == total) {
            bool f = true;
            rep(j,0,n-1) {
                int c = tmp_counts[j];
                while (c--) {
                    if (f) f = false;
                    else cout << "+";
                    cout << values[j];
                }                
            }
            cout << '\n';
            return true;
        }
        return false;
    }
    bool success = false;
    invrep(c, counts[i], 0) {
        tmp_counts[i] = c;
        success |= solve(i+1, accsum + c * values[i]);
    }
    return success;
}

int main() {
    while (true) {
        cin >> total >> n;
        if (n == 0) break;
        map<int,int> num2count;
        rep(i,1,n) {
            int x; cin >> x;
            auto it = num2count.find(x);
            if (it == num2count.end()) num2count[x] = 1;
            else it->second++;
        }
        n = num2count.size();
        int i = n-1;
        for (auto& p : num2count) {
            values[i] = p.first;
            counts[i] = p.second;
            i--;
        }
        cout << "Sums of " << total << ":\n";
        if (!solve(0, 0)) cout << "NONE\n";
    }
    return 0;
}