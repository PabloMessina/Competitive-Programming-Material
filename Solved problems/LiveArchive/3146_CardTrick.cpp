// tags: backtracking + pruning, second maximum
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
using namespace std;

#define rep(i,a,b) for (int i =a; i<=b; ++i)

typedef pair<int,int> pii;

string values[13] = {"A","2","3","4","5","6","7","8","9","10","J", "Q","K"};
string suits = "CDHS";

int toValue(string s) {
  rep(i,0,12)
    if (s == values[i])
      return i;
  return -1;
}

pii parseCard(const char* s) {
  int len = strlen(s);
  return { toValue(string(s, len-1)), suits.find(s[len-1]) };
}

pii cards[5];
char buff[4];
int perm[5];
bool used[5];

bool check() {
  pii mincard = {100, 100};
  pii maxcard1 = {-1, -1 };
  pii maxcard2 = {-1, -1 };
  int minci, maxci1, maxci2;
  rep (k, 2, 4) {
    if (cards[perm[k]] < mincard) {
      mincard = cards[perm[k]];
      minci = k;
    }
    if (maxcard1 < cards[perm[k]]) {
      maxcard2 = maxcard1;
      maxcard1 = cards[perm[k]];
      maxci2 = maxci1;
      maxci1 = k;
    } else if (maxcard2 < cards[perm[k]]) {
      maxcard2 = cards[perm[k]];
      maxci2 = k;
    }
  }
  int shift = (minci - 1) + ((maxci1 < maxci2) ? 3 : 0);
  pii aux = cards[perm[1]];
  aux.first += shift;
  if (aux.first >= 13) aux.first -= 13;
  return aux == cards[perm[0]];
}

bool search(int i) {
  rep (j, 0, 4) {
    if (!used[j]) {
      if (i == 1 && cards[perm[0]].second != cards[j].second) continue;
      perm[i] = j;
      used[j] = true;
      if (i == 4) {
        if (check()) return true;        
      } else {
        if (search(i+1)) return true;
      }      
      // backtrack
      used[j] = false;
    }
  }
  return false;
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    rep(i,0,4) {
      scanf("%s", buff);
      cards[i] = parseCard(buff);
    }
    memset(used, 0, sizeof used);
    search(0);
    rep(i,0,4) {
      pii aux = cards[perm[i]];
      if(i) printf(" ");
      printf("%s%c", values[aux.first].c_str(), suits[aux.second]);
    }
    puts("");
  }
  return 0;
}