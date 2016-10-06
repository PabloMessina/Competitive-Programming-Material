#include <bits/stdc++.h>
using namespace std;

set<char> vowels_set = {'a','e','i','o','u'};

int main() {
  string line;
  while(getline(cin, line)) {
    vector<char> vowels;
    for(char c : line) {
      if (vowels_set.find(c) != vowels_set.end()) {
        vowels.push_back(c);
      }
    }
    int i = 0, j = (int)vowels.size()-1;
    bool valid = true;
    while (i < j) {
      if (vowels[i] != vowels[j]) {
        valid = false;
        break;
      }
      i++, j--;
    }
    if (valid)
      puts("S");
    else
      puts("N");
  }
  return 0;
}