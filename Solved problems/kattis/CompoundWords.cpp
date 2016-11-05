#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

void split(string& s, vector<string>& tokens) {
  stringstream ss(s);
  string tok;
  while(getline(ss, tok, ' '))
    tokens.push_back(tok);
}

int main() {
  string line;
  vector<string> tokens;
  set<string> uniques;

  while (getline(cin, line))
    split(line, tokens);

  int n = tokens.size();
  rep(i,0,n-2) {
    rep(j,i+1,n-1) {

      uniques.insert(tokens[i] + tokens[j]);
      uniques.insert(tokens[j] + tokens[i]);
    }
  }

  for (string str : uniques) {
    puts(str.c_str());
  }

  return 0;
}