// tags: string handling, input handling

#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

void split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    if (item.size())
      elems.push_back(item);
  }
}

int main() {
  string line;

  map<string, int> word2val;
  map<int, string> val2word;

  while(getline(cin, line)) {
    vector<string> tokens;
    split(line, ' ', tokens);
    if (tokens[0] == "def") {
      string word = tokens[1];
      int val = atoi(tokens[2].c_str());

      // delete if defined before
      auto it = word2val.find(word);
      if (it != word2val.end()) {
        word2val.erase(it->first);
        val2word.erase(it->second);
      }

      // define
      word2val[word] = val;
      val2word[val] = word;

    } else if (tokens[0] == "calc") {

      int sum = 0;
      bool valid = true;

      for (int i = 1; i < tokens.size(); i+=2) {
        string word = tokens[i];
        auto it = word2val.find(word);
        if (it == word2val.end()) {
          valid = false;
          break;
        } else {
          int val = it->second;
          if (i == 1) sum = val;
          else {
            if (tokens[i-1] == "+")
              sum += val;
            else
              sum -= val;
          }
        }        
      }

      rep (i, 1, (int)tokens.size()-1) {
        printf("%s ", tokens[i].c_str());
      }
      if (!valid || (val2word.find(sum) == val2word.end())) {
        puts("unknown");
      } else {
        printf("%s\n",val2word[sum].c_str());
      }
    } else {// clear
      word2val.clear();
      val2word.clear();
    }
  }
  return 0;    
}
