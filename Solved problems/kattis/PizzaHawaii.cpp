// tags: implementation, bitmask, std::map
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,a,b) for (int i=a; i>=b; --i)
typedef long long int ll;

int T, N;
map<string,ll> foreign;
map<string,ll> native;
map<string,int> pizzaIds;
const ll bit = 1;
char buff[200];

void update_map(map<string,ll>& m, string& key, int index) {
    auto it = m.find(key);
    ll val = (it == m.end()) ? 0 : it->second;
    val |= (bit << index);
    m[key] = val;
}

int main() {
    cin >> T;
    while (T--) {
        foreign.clear();
        native.clear();
        cin >> N;
        rep(i,0,N-1) {
            string token; int m;
            cin >> token;
            cin >> m;
            while (m--) {
                cin >> token;
                update_map(foreign, token, i);
            }
            cin >> m;
            while(m--) {
                cin >> token;
                update_map(native, token, i);
            }
        }
        for(auto& i : foreign) {
            for(auto& j : native) {
                if (i.second == j.second) {
                    cout << "(" << i.first << ", " << j.first << ")\n";
                }
            }
        }
        if (T) cout << '\n';
    }
    return 0;
}