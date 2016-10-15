// tags: parse input, change base, implementation

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i <= b; ++i)
#define invrep(i,a,b) for(int i=a; i>= b; --i)

typedef long long int ll;

const ll maxval = (ll)UINT_MAX;

void split(string& s, vector<string>& tokens) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, ' '))
    tokens.push_back(item);
}

void update_base(string& s, int& base) {
  for (char c : s) {
    if ('0' <= c && c <= '9')
      base = max(base, c-'0' + 1);
    else
      base = max(base, c-'a' + 11);
  }
}

int char2int(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  return c - 'a' + 10;
}

bool try_parse_num(string& tok, ll& num, int base) {
  ll aux = 1;
  num = 0;
  invrep(i, (int)tok.size()-1, 0) {
    num += aux * char2int(tok[i]);
    aux *= base;
    if (num > maxval)
      return false;
  }
  return true;
}

bool only_ones(string& s) {
  for (char c : s)
    if (c != '1')
      return false;
  return true;
}

bool check_operation(ll a, ll b, ll c, char op) {
  switch(op) {
    case '*':
      return a * b == c;
    case '/':
      return b != 0 && (a % b == 0) && (a / b == c);
    case '+':
      return a + b == c;
    default: // -
      return a - b == c;
  }
}

string bases = "123456789abcdefghijklmnopqrstuvwxyz0";

void process_tokens(vector<string>& tokens) {
  string tokA = tokens[0];
  string tokB = tokens[2];
  string tokC = tokens[4];
  ll numA, numB, numC;
  char op = tokens[1][0];

  bool invalid = true;

  if (only_ones(tokA) && only_ones(tokB) && only_ones(tokC)) {
    numA = tokA.size();
    numB = tokB.size();
    numC = tokC.size();
    if (check_operation(numA, numB, numC, op)) {
      invalid = false;
      printf("1");
    }
  }

  int base = 2;
  update_base(tokA, base);
  update_base(tokB, base);
  update_base(tokC, base);

  for (;base <= 36; ++base) {
    if (try_parse_num(tokA, numA, base)
      && try_parse_num(tokB, numB, base)
      && try_parse_num(tokC, numC, base)
      && check_operation(numA, numB, numC, op)) 
    {
      invalid = false;
      printf("%c", bases[base-1]);
    }
  }
  if (invalid)
    puts("invalid");
  else
    puts("");
}

int main() {
  int n;
  scanf("%d\n", &n);
  string line;
  while(n--) {
    getline(cin, line);
    vector<string> tokens;
    split(line, tokens);
    process_tokens(tokens);
  }
  return 0;
}