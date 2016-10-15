#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  scanf("%d\n", &n);
  string line;
  string prefix = "Simon says";
  while(n--) {
    getline(cin, line);
    if (line.compare(0, prefix.size(), prefix) == 0) {
      printf("%s\n", line.c_str() + prefix.size() + 1);
    }
  } 
  return 0;
}