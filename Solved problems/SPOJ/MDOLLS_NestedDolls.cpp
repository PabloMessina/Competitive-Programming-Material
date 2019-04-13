// tags: greedy, implementation, std::set
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
const int MAXN = 20000;
int width[MAXN], height[MAXN];
int dolls[MAXN];
int N;
bool cmp_w (int i, int j) { return width[i] > width[j]; }
int main() {
    vector<int> pending_batch;
    pending_batch.reserve(MAXN);
    int tc; cin >> tc; // read test cases
    while (tc--) { // for each test case
        cin >> N; // read number of dolls
        rep(i,0,N-1) { // read widths and heights
            cin >> width[i] >> height[i];
            dolls[i] = i;
        }
        sort(dolls, dolls+N, cmp_w); // sort dolls decreasingly by width
        set<pair<int,int>> s; // we use this set to keep track of nested dolls
        // sorted in increasing order by height
        int last_w = -1;   
        pending_batch.clear();
        rep(i,0,N-1) { // for each doll
            int j = dolls[i];
            if (last_w != width[j]) { // if we are entering a new batch
            // of dolls (think of the dolls array as 
            // a sequence of batches of dolls, all dolls in the same batch
            // sharing the same width, and batches sorted in strictly
            // decreasing order by width)                
                // add all dolls from last pending batch to set s
                for (int x : pending_batch) s.emplace(height[x], x);
                // clear pending batch and update last width
                pending_batch.clear();
                last_w = width[j];
            }
            // find the nested doll with smallest height > doll j's height
            auto it = s.lower_bound({height[j]+1, -1});
            if (it != s.end()) s.erase(it); // remove the nested doll from the set
            //   we do this because the nested dolls is no longer available for
            //   remaining dolls in the same batch
            pending_batch.push_back(j); // remember we have to include doll j
            //   as the new nested doll (we will do that when we start processing
            //   the next batch of dolls)
        }
        // print the final number of nested dolls
        cout << s.size() + pending_batch.size() << '\n';
    }
    return 0;
}