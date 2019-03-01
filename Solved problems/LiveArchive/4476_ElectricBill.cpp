// tags: binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

ll range_size[3] = {100, 9900, 990000};
ll range_price[3] = {100 * 2, 9900 * 3, 990000 * 5};
ll price[4] = {2,3,5,7};

ll get_consumption(ll bill) {
    ll cons = 0;
    rep(i,0,2) {
        if (bill <= range_price[i]) {
            return cons + bill / price[i];
        }
        cons += range_size[i];
        bill -= range_price[i];
    }
    return cons + bill / price[3];
}

ll get_bill(ll cons) {
    ll bill = 0;
    rep(i,0,2) {
        if (cons <= range_size[i]) {
            return bill + cons * price[i];
        }
        bill += range_price[i];
        cons -= range_size[i];
    }
    return bill + cons * price[3];
}

int main() {
    ll A,B;
    while (1) {
        cin >> A >> B;
        if (A == 0) break;
        ll tot_cons = get_consumption(A);
        ll l, r, m;
        l = 0, r = tot_cons;
        while (l < r) {
            m = (l+r)/2;
            if (get_bill(tot_cons-m) - get_bill(m) <= B) r = m;
            else l = m+1;
        }
        cout << get_bill(l) << '\n';
    }
    return 0;
}