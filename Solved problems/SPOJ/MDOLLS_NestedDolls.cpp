// tags: greedy, implementation, std::set
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
const int MAXN = 20000;
int width[MAXN], height[MAXN];
int dolls[MAXN];
int N;
bool cmp (int i, int j) {
    if (width[i] == width[j]) return height[i] < height[j];
    return width[i] > width[j];
}
int main() {
    int tc; cin >> tc; // read test cases
    while (tc--) { // for each test case
        cin >> N; // read number of dolls
        rep(i,0,N-1) { // read widths and heights
            cin >> width[i] >> height[i];
            dolls[i] = i;
        }
        sort(dolls, dolls+N, cmp); // sort dolls decreasingly by width, and break
        //                            ties increasingly by height
        set<pair<int,int>> s; // we use this set to keep track of nested dolls
        //                       sorted increasingly by height
        rep(i,0,N-1) { // for each doll
            int j = dolls[i];
            // find the nested doll with smallest height > doll j's height
            auto it = s.lower_bound({height[j]+1, -1});
            if (it != s.end()) s.erase(it); // remove obsolete nested doll
            s.emplace(height[j], j); // insert new nested doll
        }
        // print the final number of nested dolls
        cout << s.size() << '\n';
    }
    return 0;
}