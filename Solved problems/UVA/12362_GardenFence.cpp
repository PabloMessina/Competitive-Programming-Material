#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
int P, L;
enum Kind { PINE, LARCH };
struct Point {
    ll x, y;    
};
Point pts[2000];
Kind kinds[2000];
int values[2000];
int main() { 
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    while (cin >> P >> L and P) {
        int totv_pine = 0;
        int totv_larch = 0;
        rep(i,0,P-1) {
            cin >> pts[i].x >> pts[i].y >> values[i];
            kinds[i] = PINE;
            totv_pine += values[i];
        }
        rep(i,P,P+L-1) {
            cin >> pts[i].x >> pts[i].y >> values[i];
            kinds[i] = LARCH;
            totv_larch += values[i];
        }
        rep(i,0,P+L-1) {
            
        }
        
    }
    return 0;
}

// #pragma GCC optimize("Ofast")
// #include <bits/stdc++.h>
// using namespace std;
// #define rep(i,a,b) for(int i = a; i <= b; ++i)
// typedef long long int ll;
// // -------------------------------
// const double PI = acos(-1);
// int P, L;
// enum Kind { PINE, LARCH };
// struct Point {
//     ll x, y;
//     Point operator-(const Point& p) const { return {x - p.y, y - p.y}; }
//     double angle() {
//         double angle = atan2(y, x);
//         if (angle < 0) angle += 2 * PI;
//         return angle;
//     }
// };
// int values[2000];
// Kind kinds[2000];
// Point pts[2000];
// int main() {
//     ios::sync_with_stdio(false); 
//     cin.tie(0); cout.tie(0);
//     while (cin >> P >> L and P > 0) {
//         int pine_totv = 0, larch_totv = 0;
//         rep(i,0,P-1) {
//             cin >> pts[i].x >> pts[i].y >> values[i];
//             pine_totv += values[i];
//             kinds[i] = PINE;
//         }
//         rep(i,P,P+L-1) {
//             cin >> pts[i].x >> pts[i].y >> values[i];
//             larch_totv += values[i];
//             kinds[i] = LARCH;
//         }
//         int ans = INT_MAX;
//         vector<pair<double,int>> pairs;
//         pairs.reserve(P+L);
//         rep(i,0,P+L-1) {
//             // printf("--------------------\n");
//             // printf("pts[i=%d] = {%lld, %lld} (kind=%s)\n",
//             //     i, pts[i].x, pts[i].y, kinds[i] == PINE ? "pine" : "larch");

//             pairs.clear();
//             rep(j,0,P+L-1) {
//                 if (i == j) continue;
//                 pairs.emplace_back((pts[j] - pts[i]).angle(), j);
//             }
//             sort(pairs.begin(), pairs.end());
//             int m = pairs.size();
//             int pine_sum = 0, larch_sum = 0;
//             if (kinds[i] == PINE) pine_sum += values[i];
//             else larch_sum += values[i];
            
//             // printf("pine_sum = %d\n", pine_sum);
//             // printf("larch_sum = %d\n", larch_sum);            
                
//             int k = -1;
//             int j = 0;
//             while (j < m) {
//                 while (1) {
//                     if (k+1 - j+1 > m) break;
//                     double delta = pairs[(k+1) % m].first - pairs[j].first;
//                     if (delta < 0) delta += 2 * PI;                    
//                     if (delta > PI) break;
//                     ++k;
//                     if (kinds[pairs[k % m].second] == PINE) pine_sum += values[pairs[k % m].second];
//                     else larch_sum += values[pairs[k % m].second];
//                     int kk = pairs[k % m].second;
//                     // printf("\t   pts[kk=%d] = {%lld, %lld} (kind=%s)\n",
//                     //     kk, pts[kk].x, pts[kk].y, kinds[kk] == PINE ? "pine" : "larch");
//                 }
//                 // printf("   pine_sum = %d\n", pine_sum);
//                 // printf("   larch_sum = %d\n", larch_sum);
//                 assert (larch_sum <= larch_totv);
//                 assert (pine_sum <= pine_totv);
//                 int cost1 = pine_sum + larch_totv - larch_sum;
//                 int cost2 = larch_sum + pine_totv - pine_sum;
//                 int cost = min(cost1, cost2);
//                 // printf("  cost1 =%d, cost2 = %d, cost = %d\n", cost1, cost2, cost);
//                 ans = min({ans, cost});
                
//                 // printf("    ** pine_sum = %d\n", pine_sum);
//                 // printf("    ** larch_sum = %d\n", larch_sum);
//                 do {
//                     if (kinds[pairs[j].second] == PINE) pine_sum -= values[pairs[j].second];
//                     else larch_sum -= values[pairs[j].second];
//                     ++j;
//                 }
//                 while (j < m and abs(pairs[j].first - pairs[j-1].first) < 1e-8);
//             }
//         }
//         cout << ans << '\n';
//     }
//     return 0;
// }