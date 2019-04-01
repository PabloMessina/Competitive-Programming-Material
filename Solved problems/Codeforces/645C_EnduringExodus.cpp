// tags: two pointers
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
int N,K;
vector<int> empty_rooms;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> N >> K;
    string line; cin >> line;
    int i = 0;
    empty_rooms.reserve(N);
    for (char c : line) {
        if (c == '0') empty_rooms.push_back(i);
        i++;
    }
    int M = empty_rooms.size();
    int j = 0;
    int ans = INT_MAX;
    int curr, next;
    rep(i,0,M-K-1) {
        while (true) {
            curr = max(empty_rooms[j] - empty_rooms[i], empty_rooms[i+K] - empty_rooms[j]);
            next = max(empty_rooms[j+1] - empty_rooms[i], empty_rooms[i+K] - empty_rooms[j+1]);
            if (next < curr) ++j;
            else break;
        }
        ans = min(ans, curr);
    }
    cout << ans << '\n';
    return 0;
}