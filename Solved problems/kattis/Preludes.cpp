#include <bits/stdc++.h>
using namespace std;

map<string,string> dict = {
  {"A","A"},
  {"A#","Bb"}, {"Bb","A#"},
  {"B","B"},
  {"C","C"},
  {"C#","Db"}, {"Db","C#"},
  {"D","D"},
  {"D#","Eb"}, {"Eb","D#"},
  {"E","E"},
  {"F","F"},
  {"F#","Gb"}, {"Gb","F#"},
  {"G","G"},
  {"G#","Ab"}, {"Ab","G#"}
};

int main() {
  string line, note, ton, eq;
  int c = 1;
  while (getline(cin, line)) {
    stringstream ss(line);
    getline(ss, note, ' ');
    getline(ss, ton, ' ');
    eq = dict[note];
    printf("Case %d: ", c++);
    if (eq == note) {
      puts("UNIQUE");
    } else {
      printf("%s %s\n", eq.c_str(), ton.c_str());
    }
  }
  return 0;
}