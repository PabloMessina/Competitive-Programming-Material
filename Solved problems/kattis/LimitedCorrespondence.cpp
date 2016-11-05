#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXK 11

int K;
vector<string> s1, s2;
char buff1[101];
char buff2[101];

bool best_found = false;
char best[MAXK * 100 + 1];
int blen;

char accstr1[MAXK * 100 + 1];
char accstr2[MAXK * 100 + 1];
int acclen1 = 0;
int acclen2 = 0;

bool used[MAXK];

void search(int next) {
  
  const char* a = s1[next].c_str();
  const char* b = s2[next].c_str();
  int la = s1[next].size();
  int lb = s2[next].size();
  memcpy(accstr1 + acclen1, a, la);
  memcpy(accstr2 + acclen2, b, lb);
  
  int min_len_bef = min(acclen1, acclen2);
  int min_len_aft = min(acclen1+la, acclen2+lb);  
  int max_len_aft = max(acclen1+la, acclen2+lb);

  // check valid string expansions
  if (memcmp(accstr1 + min_len_bef,
            accstr2 + min_len_bef,
            min_len_aft - min_len_bef) != 0)
    return;

  if (best_found) {

    // check not longer than best solution    
    if (blen < max_len_aft)
      return;

    // if same length as best solution
    if (blen == max_len_aft) {
      // both strings should have same size
      if (min_len_aft < max_len_aft)
        return;

      // the whole string should be less than best
      if (memcmp(accstr1, best, blen) >= 0)
        return;

      // update best string
      memcpy(best, accstr1, blen);
      best[blen] = '\0';
      return;

    }

  }

  // -------------------------------
  // no best or smaller than best

  // solution found
  if (min_len_aft == max_len_aft) {

    // update best
    memcpy(best, accstr1, min_len_aft);
    best[min_len_aft] = '\0';
    blen = min_len_aft;
    best_found = true;

  // keep backtracking
  } else {

    used[next] = true;
    acclen1 += la;
    acclen2 += lb;

    rep(i, 0, K-1) {
      if (!used[i]) {
        search(i);
      }
    }

    used[next] = false;
    acclen1 -= la;
    acclen2 -= lb;
  }

}

int main() {
  string line;
  int _case = 1;
  while(scanf("%d\n",&K)==1) {

    s1.clear();
    s2.clear();
    rep(i,1,K) {
      scanf("%s%s", buff1, buff2);
      string a(buff1), b(buff2);
      s1.push_back(a);
      s2.push_back(b);
    }

    memset(used, 0, sizeof used);
    acclen1 = 0;
    acclen2 = 0;
    blen = 0;
    best_found = false;

    rep (i, 0, K-1) {
      search(i);
    }

    printf("Case %d: ", _case++);
    if (best_found) {
      puts(best);
    } else {
      puts("IMPOSSIBLE");
    }

  }
  return 0;
}