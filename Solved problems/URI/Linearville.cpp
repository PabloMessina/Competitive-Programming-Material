// tags: greedy, implementation, adhoc
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------

const int MAXN = 100000;
int N;
int accX[MAXN], accY[MAXN];
int leftX[MAXN], rightX[MAXN], upY[MAXN], downY[MAXN];

int inline manhattan(int ax, int ay, int bx, int by) {
    return abs(accX[bx] - accX[ax]) + abs(accY[by] - accY[ay]);
}

int mindist(int ax, int ay, int bx, int by) {
    int stepsx = abs(bx - ax);
    int stepsy = abs(by - ay);
    int steps_delta = abs(stepsx - stepsy);
    if (steps_delta <= 1) return manhattan(ax, ay, bx, by);
    int ans = manhattan(ax, ay, bx, by) + 5 * (steps_delta - (steps_delta&1));
    if (stepsy > stepsx) { // vertical overflow
        if (rightX[ax] != -1) { // width-1 column rightwards
            int d = rightX[ax] - ax;
            int ax2 = ax + d;
            int ay2 = by > ay ? ay + d : ay - d;
            int stepsx2 = abs(bx - ax2);
            int stepsy2 = abs(by - ay2);
            if (stepsy2 > stepsx2) {                
                int steps_delta2 = stepsy2 - stepsx2;
                ans = min(ans, manhattan(ax, ay, ax2, ay2) + manhattan(ax2, ay2, bx, by) + (steps_delta2 - (steps_delta2&1)));
            }
        }
        if (leftX[ax] != -1) { // width-1 column leftwards
            int d = ax - leftX[ax];
            int ax2 = ax - d;
            int ay2 = by > ay ? ay + d : ay - d;
            int stepsx2 = abs(bx - ax2);
            int stepsy2 = abs(by - ay2);
            if (stepsy2 > stepsx2) {
                int steps_delta2 = stepsy2 - stepsx2;
                ans = min(ans, manhattan(ax, ay, ax2, ay2) + manhattan(ax2, ay2, bx, by) + (steps_delta2 - (steps_delta2&1)));
            }
        }
    } else { // horizontal overflow
        if (upY[ay] != -1) { // width-1 row upwards
            int d = upY[ay] - ay;
            int ay2 = ay + d;
            int ax2 = bx > ax ? ax + d : ax - d;
            int stepsx2 = abs(bx - ax2);
            int stepsy2 = abs(by - ay2);
            if (stepsx2 > stepsy2) {
                int steps_delta2 = stepsx2 - stepsy2;
                ans = min(ans, manhattan(ax, ay, ax2, ay2) + manhattan(ax2, ay2, bx, by) + (steps_delta2 - (steps_delta2&1)));
            }
        }
        if (downY[ay] != -1) { // width-1 row downwards
            int d = ay - downY[ay];
            int ay2 = ay - d;
            int ax2 = bx > ax ? ax + d : ax - d;
            int stepsx2 = abs(bx - ax2);
            int stepsy2 = abs(by - ay2);
            if (stepsx2 > stepsy2) {
                int steps_delta2 = stepsx2 - stepsy2;
                ans = min(ans, manhattan(ax, ay, ax2, ay2) + manhattan(ax2, ay2, bx, by) + (steps_delta2 - (steps_delta2&1)));
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    int tmp;
    // horizontal axis
    accX[0] = 0;
    rep(i,1,N-1) {
        cin >> tmp;
        accX[i] = accX[i-1] + tmp;
    }
    tmp = -1;
    rep(i,0,N-1) {
        if (i > 0 and accX[i] - accX[i-1] == 1) tmp = i;
        leftX[i] = tmp;
    }
    tmp = -1;
    invrep(i,N-1,0) {
        if (i < N-1 and accX[i+1] - accX[i] == 1) tmp = i;
        rightX[i] = tmp;
    }
    // vertical axis
    accY[0] = 0;
    rep(i,1,N-1) {
        cin >> tmp;
        accY[i] = accY[i-1] + tmp;
    }
    tmp = -1;
    rep(i,0,N-1) {
        if (i > 0 and accY[i] - accY[i-1] == 1) tmp = i;
        downY[i] = tmp;
    }
    tmp = -1;
    invrep(i,N-1,0) {
        if (i < N-1 and accY[i+1] - accY[i] == 1) tmp = i;
        upY[i] = tmp;
    }
    // queries
    int Q; cin >> Q;
    while (Q--) {
        int ax, ay, bx, by;
        cin >> ax >> ay >> bx >> by;
        --ax, --ay, --bx, --by;
        cout << mindist(ax, ay, bx, by) << '\n';
    }
    return 0;
}   