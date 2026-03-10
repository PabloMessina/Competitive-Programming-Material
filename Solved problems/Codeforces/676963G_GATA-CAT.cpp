// tags: greedy, prefix sums
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
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
signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int Q; cin >> Q;
    vector<char> bank;
    rep(i,0,125) { bank.pb('A'); bank.pb('T'); }
    bank.pb('A');
    int bs = bank.size();
    vector<int> a_count(bs, 0);
    vector<int> t_count(bs, 0);
    vector<int> at_count(bs, 0);
    vector<int> ta_count(bs, 0);
    vector<int> ata_count(bs, 0);
    invrep(i,bs-1,0) {
        if (i+1 < bs) {
            a_count[i] = a_count[i+1];
            t_count[i] = t_count[i+1];
            at_count[i] = at_count[i+1];
            ta_count[i] = ta_count[i+1];
            ata_count[i] = ata_count[i+1];
        }
        if (bank[i] == 'A') a_count[i]++;
        if (bank[i] == 'T') t_count[i]++;
        if (bank[i] == 'A' and i+1 < bs) at_count[i] += t_count[i+1];
        if (bank[i] == 'T' and i+1 < bs) ta_count[i] += a_count[i+1];
        if (bank[i] == 'A' and i+1 < bs) ata_count[i] += ta_count[i+1];
    }
    while (Q--) {
        int G, C; cin >> G >> C;
        vector<int> g_count(bs), c_count(bs);
        int l = 0, r = bs;
        rep(i,0,bs) {
            if (ata_count[i] <= G and ata_count[i] > 0) {
                g_count[i] = G / ata_count[i];
                G %= ata_count[i];
            }
        }
        assert (G == 0);
        rep(i,0,bs) {
            if (at_count[i] <= C and at_count[i] > 0) {
                c_count[i] = C / at_count[i];
                C %= at_count[i];
            }
        }
        assert (C == 0);
        string line = "";
        rep(i,0,bs) {
            while (g_count[i]-- > 0) line += 'G';
            while (c_count[i]-- > 0) line += 'C';
            line += bank[i];
        }
        int idx = min(line.find('G'), line.find('C'));
        if (idx == string::npos) idx = bs-1;
        line = line.substr(idx);
        cout << line << '\n';
    }
    return 0;
}