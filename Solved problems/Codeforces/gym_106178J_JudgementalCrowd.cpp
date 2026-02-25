// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    int score = 0;
    string query;
    // Check for "ha" matches
    query = "ha";
    if (s.size() >= query.size()) {
        rep(i,0,s.size()-query.size()+1) {
            if (s.compare(i, query.size(), query) == 0) {
                score++;
            }
        }
    }
    // Check for "boooo" matches
    query = "boooo";
    if (s.size() >= query.size()) {
        rep(i,0,s.size()-query.size()+1) {
            if (s.compare(i, query.size(), query) == 0) {
                score--;
            }
        }
    }
    // Check for "bravo" matches
    query = "bravo";
    if (s.size() >= query.size()) {
        rep(i,0,s.size()-query.size()+1) {
            if (s.compare(i, query.size(), query) == 0) {
                score+=3;
            }
        }
    }
    cout << score << '\n';
    return 0;
}