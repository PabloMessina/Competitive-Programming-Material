// tags: implementation, std::set
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const int MAXN = 500000;
int boxes[MAXN];
int pop[MAXN];
int score[MAXN];
bool cmp(int i, int j) {
    if (score[i] == score[j]) return i < j;
    return score[i] > score[j];
}
int main() {
    while (true) {
        int N, B; cin >> N >> B;
        if (N==-1) break;
        set<int, bool(*)(int,int)> ranking(cmp);
        rep(i,0,N-1) {
            cin >> pop[i];
            score[i] = pop[i];
            boxes[i] = 1;
            ranking.insert(i);
        }
        B -= N;
        while (B--) {
            auto it = ranking.begin();
            int i = *it;
            ranking.erase(it);
            boxes[i]++;
            score[i] = (pop[i] / boxes[i]) + (pop[i] % boxes[i] > 0);
            ranking.insert(i);
        }
        cout << score[*ranking.begin()] << '\n';
    }
    return 0;
}