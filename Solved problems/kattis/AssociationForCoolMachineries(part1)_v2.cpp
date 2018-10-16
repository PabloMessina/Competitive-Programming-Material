// tags: simulation, implementation,
// shortest repeating cycle (KMP)
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> iii;
#define rep(i,a,b) for(int i=a; i<=b; i++)

const int MAXN = 200;
int N;
int sr, sc;
string program;
string grid[MAXN];
int states[MAXN][MAXN][MAXN];

int inline hash_cell(int r, int c) { return N * r + c; }

int shortest_repeating_cycle(vector<int>& sequence) {
    // KMP : lps step
    int n = sequence.size();
    int lps[n];
    lps[0] = 0;
    int i = 0, j = 1;
    while (j < n) {
        while (i > 0 and sequence[i] != sequence[j])
            i = lps[i-1];
        if (sequence[i] == sequence[j])
            lps[j] = ++i;
        else
            lps[j] = 0;
        j++;
    }
    int len = n - lps[n-1];
    return (n % len) ? n : len;
}

int main() {
    // --- increase cin's performance
    ios::sync_with_stdio(false);
    cin.tie(0);
    // --- read input
    cin >> N >> program;    
    rep(i,0,N-1) cin >> grid[i];
    // --- find starting position
    rep(i,0,N-1) rep(j,0,N-1) {
        if (grid[i][j] == 'R') {
            sr = i; sc = j; goto simulation;
        }
    }
    // --- simulate and find loop in states
    simulation:
    vector<iii> state_sequence;
    vector<int> trail;
    state_sequence.reserve(N * N * N);
    trail.reserve(N * N * N);
    int psize = program.size();
    int r = sr, c = sc, p = 0;
    int i = 0;
    memset(states, -1, sizeof states);
    while (states[r][c][p] == -1) {
        states[r][c][p] = i++;
        state_sequence.emplace_back(r,c,p);
        int dr, dc;
        switch(program[p]) {
            case '<':
            dr = 0, dc = -1; break;
            case '>':
            dr = 0, dc = 1; break;
            case 'v':
            dr = 1, dc = 0; break;
            case '^':
            dr = -1, dc = 0; break;
            default:
            assert (false); // this should never happen
        }
        int rr = r + dr;
        int cc = c + dc;
        if (grid[rr][cc] != '#') {
            r = rr; c = cc;
        }
        p = (p + 1) % psize;
    }
    assert (states[r][c][p] != -1); // this should be true    
    // --- find trail associated to loop in states
    int loop_start = states[r][c][p];
    int len = state_sequence.size();
    int prev_r = -1, prev_c = -1;
    rep(j, loop_start, len-1) {
        auto& s = state_sequence[j];
        int r = get<0>(s);
        int c = get<1>(s);        
        if (r != prev_r or c != prev_c) {
            trail.push_back(hash_cell(r,c));
        }
        prev_r = r; prev_c = c;
    }
    // --- make sure first and last elements in trail are not the same
    if (trail.size() > 1 and trail[0] == trail.back())
        trail.pop_back();
    // --- find minimum cycle in trail
    cout << shortest_repeating_cycle(trail) << endl;
    return 0;
}