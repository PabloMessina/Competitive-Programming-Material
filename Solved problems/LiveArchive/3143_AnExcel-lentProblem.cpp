#include <cstdio>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
using namespace std;

#define MAXR 300000000
#define MAXLOG 20
#define rep(i,a,b) for(int i=a; i <= b; ++i)
#define invrep(i,b,a) for(int i=b; i>=a; --i)


typedef long long int ll;

ll MS[MAXLOG+1][27];
ll NMS[MAXLOG+1][27];

void DP() {
  rep(c,1,26) MS[0][c] = c;
  rep(c,1,26) NMS[0][c] = c;
  rep(i,1,MAXLOG) {
    rep(c,1,26) {
      ll aux = 0;
      rep(j,0,i-2) aux += NMS[j][26];
      MS[i][c] = MS[i-1][26] + aux * c + NMS[i-1][26] * (c-1);
      NMS[i][c] = (NMS[i-1][26] + aux) * (c-1);
    }
  }
}

ll string2Num(string& s) {
  ll num = MS[s.size()-1][s[0]-'A' + 1];
  rep(i,1,s.size()-1) 
    num += NMS[s.size()-1-i][s[i]-'A' + 1];
  return num;
}

int main () {

  DP();

  string test1 = "YYZ";
  string test2 = "YZZ";
  printf("%s = %lld\n",test1.c_str(), string2Num(test1));
  printf("%s = %lld\n",test2.c_str(), string2Num(test2));

  string line;
  while(true) {

    getline(cin, line);
    std::size_t pos = line.find('C');
    ll r = (ll)atoi(line.substr(1, pos - 1).c_str());
    ll c = (ll)atoi(line.substr(pos + 1).c_str());
    if (r == 0 && c == 0) break;



    printf("%lld\n", r);
  }
  return 0;
}