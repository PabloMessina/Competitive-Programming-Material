// tags: implementation, std::set
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
struct Interval {
    int i, j, c;
    bool operator<(const Interval& o) const { return i < o.i; }
};
int L, C, N;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> L >> C >> N) {
        set<Interval> s;
        vector<int> freq(C+1, 0);
        freq[1] = L;
        s.insert({0, L-1, 1});
        while (N--) {
            int P, X, A, B;
            cin >> P >> X >> A >> B;
            ll S = freq[P];
            int m1 = (A + S * S) % (ll)L;
            int m2 = (A + (S + B) * (S + B)) % (ll)L;
            if (m1 > m2) swap(m1, m2);
            freq[X] += m2 - m1 + 1;
            Interval i = {m1, m2, X};
            auto it1 = s.lower_bound(i);
            if (it1 != s.begin() and prev(it1)->j >= m1) --it1;
            auto it2 = next(it1);
            while (it2 != s.end() and it2->i <= m2) ++it2;
            for (auto it = it1; it != it2; ++it) {
                int b = max(it->i, m1);
                int e = min(it->j, m2);
                freq[it->c] -= e - b + 1;
            }
            Interval ib = *it1;
            Interval ie = *prev(it2);
            s.erase(it1, it2);
            s.insert(i);
            if (ib.i < m1) s.insert({ib.i, m1-1, ib.c});
            if (ie.j > m2) s.insert({m2+1, ie.j, ie.c});
        }
        cout << *max_element(freq.begin(), freq.end()) << '\n';
    }
    return 0;
}