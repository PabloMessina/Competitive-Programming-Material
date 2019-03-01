#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
using namespace std;

int B,Z;
int next[10][101];
int count[101] = {0};
bool vis[10][101] = {0};
vector<int> trace[10];
int cycle_offset[10];
int cycle_size[10];
int z2index[10][101];
vector<ll> R, M;

int CRT(vector<ll>& R, vector<ll>& M) {
    
}

int main() {
    cin >> B >> Z;
    int P,T;
    T = INT_MAX;
    rep(b,0,B-1) {
        int tmp; cin >> tmp;
        trace[b].push_back(tmp);
        count[tmp]++;
        z2index[tmp] = 0;
        vis[b][tmp] = true;
        rep(z,1,Z) cin >> next[b][z];
    }
    rep(z,1,Z) if (count[z] == B) {
        P = z; T = 0; goto answer;
    }
    rep(t,1,Z) {
        rep(b,0,B-1) {
            int curr = trace[b].back();
            int nxt = next[b][curr];
            if (vis[nxt]) {
                if (!cycle_size[b]) {
                    cycle_offset[b] = z2index[b][nxt];
                    cycle_size[b] = trace[b].size() - cycle_offset[b];
                }
            } else {
                z2index[b][nxt] = trace[b].size();
                vis[nxt] = true;
            }
            count[curr]--;
            count[nxt]++;
            trace[b].push_back(nxt);
        }
        rep(z,1,Z) if (count[z] == B) {
            P = z; T = t; goto answer;
        }
    }
    rep(b,0,B-1) { assert (cycle_size[b] > 0); }
    int freq[Z+1] = {0};
    rep(b,0,B-1) {
        rep(i,0,cycle_size[b]-1) {
            freq[trace[cycle_offset[b] + i]]++;
        }
    }
    R.resize(B);
    M.resize(B);
    rep(z,1,Z) {
        if (freq[z] == B) {
            rep(b,0,B-1) {
                R[b] = ((z2index[z] - cycle_offset[b]) - 
                    (z2index[b][trace[b].back()] - cycle_offset[b])
                    + cycle_size[b]) % cycle_size[b];
                M[b] = cycle_size[b];                
            }
            int t = CRT(R, M);
            if (t != -1 && Z + t < T) { T = Z + t; P = z; }
        }
    }
    answer:
    if (T == INT_MAX) cout << "*\n";
    else cout << P << ' ' << T << '\n';
    return 0;
}