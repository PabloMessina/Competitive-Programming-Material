// tags: implementation, recursion
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int NORMAL = 0, REVERSED = 1;
string input;

bool isvowel[26] = {0};
string vowels = "aeiou";
int vowcount[100000];
int nvowels(int l, int r) {
    return l > 0 ? (vowcount[r] - vowcount[l-1]) : vowcount[r];
}

ll count_ways(int l, int r, int d) {
    if (l==r) return 1;
    bool isvowl = isvowel[input[l]-'a'];
    bool isvowr = isvowel[input[r]-'a'];
    if (d == NORMAL) {
        if (isvowl) {
            if (isvowr) { // case V-V
                return count_ways(l+1,r,REVERSED);
            } else { // case V-C
                return count_ways(l,r-1,NORMAL) +
                    count_ways(l+1,r,REVERSED);
            }
        } else { // case C-?
            int nvows = nvowels(l,r);
            return (nvows > 0) ? 0 : 1;
        }
    } else {
        if (isvowr) {
            if (isvowl) { // case V-V
                return count_ways(l,r-1,NORMAL);
            } else { // case V-C
                return count_ways(l+1,r,REVERSED) +
                    count_ways(l,r-1,NORMAL);
            }
        } else { // case C-?
            int nvows = nvowels(l,r);
            return (nvows > 0) ? 0 : 1;
        }
    }
}

int main() {
    for (char c : vowels)
        isvowel[c-'a'] = true;

    while(getline(cin, input)) {
        memset(vowcount, 0, sizeof vowcount);
        int len = input.size();
        int count = 0;
        rep(i,0,len-1) {
            if (isvowel[input[i]-'a']) count++;
            vowcount[i] = count;
        }
        cout << count_ways(0,len-1,NORMAL) << endl;
    }
    return 0;
}