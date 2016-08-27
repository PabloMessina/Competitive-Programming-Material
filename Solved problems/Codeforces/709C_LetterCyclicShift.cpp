#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;++i)

int main() {
  string line;
  int i,j;
  getline(cin, line);
  int n = line.size();
  i = 0;
  while (line[i] == 'a' && i < n-1) ++i;
  j = i;
  while (j < n-1 && line[j+1] != 'a') ++j;

  rep(k,i,j) 
    line[k] = (char)('a' + ((26 + (line[k] - 'a' - 1)) % 26));

  printf("%s\n", line.c_str());
  return 0;
}