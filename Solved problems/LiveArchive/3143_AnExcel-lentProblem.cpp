// tags: finding patterns in number sequences
#include <cstdio>
#include <string>
#include <iostream>
#include <cstdlib> 
#include <vector>
using namespace std;

typedef long long int ll;

void toBase(int b, int x, vector<int>& digits) {
  do {
    digits.push_back(x % b);
  } while (x /= b);
}

void getDigits(int x, vector<int>& digits) {
  int count = 1;
  ll aux = 26;
  while (x >= aux) {
    x -= aux;
    aux *= 26;
    count++;
  }
  toBase(26, x, digits);
  while (digits.size() < count) digits.push_back(0);
}

int main() {
  string line;
  while (true) {
    getline(cin, line);
    std::size_t pos = line.find('C');
    int row = atoi(line.substr(1, pos-1).c_str());
    int col = atoi(line.substr(pos+1).c_str());
    if (row == 0 && col == 0) break;
    vector<int> digits;
    getDigits(col-1, digits);
    for (int i = (int)digits.size()-1; i >= 0; --i)
      printf("%c", (char)(digits[i] + 'A'));
    printf("%d\n", row);
  }
  return 0;
}