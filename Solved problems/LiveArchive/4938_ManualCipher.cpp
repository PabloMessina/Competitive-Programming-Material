// tags: string manipulation
#include <bits/stdc++.h>
using namespace std;

string lowkeys = "abcdefghijklmnopqrstuvwxyz ";
string upkeys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

int main() {
  string line;
  // first line
  getline(cin, line);
  std:size_t pos = line.find(':');
  vector<int> offsets, digits;
  for (int i = 0; i < pos; ++i)
    offsets.push_back(line[i]-'A');
  for (int i = pos+1; i < line.size(); ++i)
    digits.push_back(line[i] - '0');

  // next lines
  while(getline(cin, line)) {
    int level = 0;
    int count = 0;
    for (char c : line) {
      int i = (c == ' ') ? 26 : (c - 'A');
      i = (27 + (i - offsets[level])) % 27;
      printf("%c", lowkeys[i]);

      if (++count == digits[level]) {
        count = 0;
        if (++level == digits.size())
          level = 0;
      }
    }
    puts("");
  }  

  return 0;
}