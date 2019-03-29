// tags: greedy, implementation, std::priority_queue
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const int MAXN = 500000;
int boxes[MAXN];
int pop[MAXN];
int score[MAXN];
struct cmp {
    bool operator()(int i, int j) { return score[i] < score[j]; }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    while (true) {
        int N, B; cin >> N >> B;
        if (N==-1) break;
        priority_queue<int, vector<int>, cmp> pq;
        rep(i,0,N-1) {
            cin >> pop[i];
            score[i] = pop[i];
            boxes[i] = 1;
            pq.push(i);
        }
        B -= N;
        while (B--) {
            int i = pq.top(); pq.pop();
            boxes[i]++;
            score[i] = (pop[i] / boxes[i]) + (pop[i] % boxes[i] > 0);
            pq.push(i);
        }
        cout << score[pq.top()] << '\n';
    }
    return 0;
}