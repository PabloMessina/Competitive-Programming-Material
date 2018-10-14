// tags: implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int f[1001];
int main() {
    int k, n;
    while (cin >> k >> n) {
        memset(f, 0, sizeof(int) * (k+1));
        rep(i,0,n-1) {
            int x; cin >> x;
            f[x]++;            
        }
        int fmin = INT_MAX, fmax = INT_MIN;
        int xmin, xmax;
        rep(x,1,k) {
            if (fmin > f[x]) {
                fmin = f[x];
                xmin = x;
            }
            if (fmax < f[x]) {
                fmax = f[x];
                xmax = x;
            }
        }
        
        assert (fmax != fmin);

        if (fmax - fmin > 2) {
            cout << "*\n";
            continue;
        }
        if (fmax - fmin == 2) {
            bool possible = true;
            rep(x,1,k) {
                if (x == xmin or x == xmax) continue;
                if (f[x] != fmin + 1) {
                    possible = false;
                    break;
                }
            }
            if (possible) {
                cout << "-" << xmax << " +" << xmin << endl;
            } else {
                cout << "*\n";
            }
        } else {
            assert (fmax - fmin == 1);
            
            option1:
            rep(x,1,k) {
                if (x == xmin or x == xmax) continue;
                if (f[x] != fmax) goto option2;
            }
            cout << "+" << xmin << endl;
            continue;

            option2:
            rep(x,1,k) {
                if (x == xmin or x == xmax) continue;
                if (f[x] != fmin) goto ggwp;
            }
            cout << "-" << xmax << endl;
            continue;

            ggwp:
            cout << "*\n";
            continue;
        }
    }
    return 0;
}