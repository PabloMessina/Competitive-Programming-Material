// tags: simulation, shortest repeating cycle (KMP)
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define rep(i,a,b) for(int i=a; i<=b; i++)

#define MAXN 300
int N;
char board[MAXN][MAXN+1];
string commands;
map<char,ii> char2move = {
    {'<', ii(0, -1)},
    {'>', ii(0, 1)},
    {'^', ii(-1, 0)},
    {'v', ii(1, 0)}
};

int main() {
    while (scanf("%d\n",&N) == 1) {
        getline(cin,commands);
        int curr_r, curr_c;
        rep(r,0,N-1) {
            scanf("%s",board[r]);
            rep(c,0,N-1) {
                if (board[r][c] == 'R')
                    curr_r = r, curr_c = c;
            }
        }

        map<ii, int> state2idx;
        vector<int> trail;
        int curr_comm_i = 0;
        int curr_cell, prev_cell = -1;
        int loop_start_i = -1;
        int n_comms = (int) commands.size();

        // simulate states until a loop is found        
        while (true) {
            curr_cell = curr_r * N + curr_c;
            ii state(curr_cell, curr_comm_i);

            auto it = state2idx.find(state);
            if (it != state2idx.end()) {
                loop_start_i = it->second;
                break;
            }

            if (curr_cell != prev_cell)
                trail.push_back(curr_cell);

            int idx = (int) trail.size() - 1;
            state2idx[state] = idx;
            
            ii move = char2move[commands[curr_comm_i]];
            int r = curr_r + move.first;
            int c = curr_c + move.second;
            if (board[r][c] != '#') curr_r = r, curr_c = c;

            curr_comm_i = (curr_comm_i + 1) % n_comms;
            prev_cell = curr_cell;        
        }

        // make sure we remove possible redundant last char
        // in trail's ending loop
        if (trail.back() == trail[loop_start_i])
            trail.pop_back();

        int m = trail.size();
        int loop_size = m - loop_start_i;
        if (loop_size < 2) {
            puts("1");
        } else {
            
            // KMP : lps step
            int lps[loop_size];
            lps[0] = 0;
            int i = 0, j = 1;
            int offset = loop_start_i;
            while (j < loop_size) {
                while (i > 0 and trail[offset + i] != trail[offset + j])
                    i = lps[i-1];
                if (trail[offset + i] == trail[offset + j])
                    lps[j] = ++i;
                else
                    lps[j] = 0;
                j++;
            }

            // print smallest cycle size
            int len = loop_size - lps[loop_size-1];
            if (len == loop_size or (loop_size % len != 0))
                printf("%d\n", loop_size);
            else
                printf("%d\n", len);
        }
    }

    return 0;
}