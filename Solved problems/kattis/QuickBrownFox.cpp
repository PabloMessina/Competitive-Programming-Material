#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;++i)

bool found[26];
int main() {
  int n;
  scanf("%d\n", &n);
  string line;
  while(n--) {
    getline(cin, line);
    memset(found, 0, sizeof found);
    for (char c : line) {
      if ('a' <= c && c <= 'z')
        found[c-'a'] = true;
      else if ('A' <= c && c <= 'Z')
        found[c-'A'] = true;
    }
    vector<char> missing;
    rep(i,0,25) {
      if (!found[i]) missing.push_back((char)('a' + i));
    }
    if (missing.size() == 0) {
      puts("pangram");
    } else {
      printf("missing ");
      for (char c : missing)
        printf("%c", c);
      puts("");
    }
  }
  return 0;
}