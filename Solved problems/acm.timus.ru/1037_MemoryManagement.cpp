#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <cstdio>
using namespace std;

#define FOR(i,i0,in) for(int i = i0; i <= in; ++i)

struct Busy {
  int index;
  int deadline;
  Busy(int i, int d) : index(i), deadline(d) {}
};

void split(const string &s, char delim, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
}

int main() {
  string line;
  vector<int> deadlines(30001, -1);
  priority_queue<int, vector<int>, greater<int> > frees;
  FOR(i,1,30000)
    frees.push(i);
  queue<Busy> busies;

  while (getline(cin, line)) {
    vector<string> tokens;
    split(line, ' ', tokens);

    int time = atoi(tokens[0].c_str());
    while (!busies.empty()) {
      Busy front = busies.front();
      if (front.deadline <= time) {
        busies.pop();
        if (front.deadline == deadlines[front.index]) {
          frees.push(front.index);
          deadlines[front.index] = -1;
        }
      } else {
        break;
      }
    }
    if (tokens.size() == 2) { // allocate
      int f = frees.top(); frees.pop();
      int t = time + 600;
      busies.push(Busy(f, t));
      deadlines[f] = t;
      printf("%d\n", f);
    } else { // access
      int address = atoi(tokens[2].c_str());
      if (deadlines[address] == -1) puts("-");
      else {
        puts("+");
        int t = time + 600;
        deadlines[address] = t;
        busies.push(Busy(address, t));
      }
    }
  }
  return 0;
}
