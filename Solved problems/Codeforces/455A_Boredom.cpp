// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = 100000;
int values[MAXN];
ll scores[MAXN];
ll memo[MAXN];
int N;

int main() {
    int n; scanf("%d", &n);
    // map values to counts
    map<int,int> dict;
    while (n--) {
        int a; scanf("%d", &a);
        auto i = dict.find(a);
        if (i == dict.end()) dict[a] = 1;
        else i->second++;
    }
    // collect values and scores in separate arrays
    N = dict.size();
    int j = 0;
    for (auto& i : dict) {
        values[j] = i.first;
        scores[j] = (ll)i.first * (ll)i.second;
        j++;
    }
    // find max score with bottom-up DP
    memo[0] = scores[0];
    memo[1] = (values[0] + 1 == values[1]) ? max(scores[1], scores[0]) : (scores[1] + scores[0]);
    rep(i,1,N-1) {
        memo[i] = (values[i-1] + 1 == values[i]) ?
            max(scores[i] + memo[i-2], memo[i-1]) :
            (scores[i] + memo[i-1]);
    }
    printf("%I64d\n", memo[N-1]);
    return 0;
}