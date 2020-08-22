// tags: implementation, simulation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
enum { ALLOC, ACCESS, FREE };
struct Event {
    int t, id, type, block;
    bool operator<(const Event& o) const { return tie(t, id) > tie(o.t, o.id); }
};
int N = 30000, T = 10 * 60;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    priority_queue<Event> events;
    priority_queue<int, vector<int>, greater<int>> free_blocks;
    vector<bool> isfree(N, true);
    vector<int> free_time(N, -1);
    rep(i,0,N) free_blocks.push(i);
    string line;
    int id = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        int t; char op; ss >> t >> op;
        if (op == '+') {
            events.push({t, id, ALLOC, -1});
        } else {
            int block; ss >> block; --block;
            events.push({t, id, ACCESS, block});
        }
        ++id;
    }
    while (events.size()) {
        Event e = events.top(); events.pop();
        if (e.type == ACCESS) {
            if (!isfree[e.block]) {
                cout << "+\n";
                free_time[e.block] = e.t + T;
                events.push({e.t + T, -1, FREE, e.block});
            } else {
                cout << "-\n";
            }
        } else if (e.type == ALLOC) {
            int block = free_blocks.top();
            free_blocks.pop();
            free_time[block] = e.t + T;
            isfree[block] = false;
            events.push({e.t + T, -1, FREE, block});
            cout << (block + 1) << '\n';
        } else if (free_time[e.block] == e.t and !isfree[e.block]) {
            isfree[e.block] = true;
            free_blocks.push(e.block);
        }
    }
    return 0;
}