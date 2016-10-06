#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,a,b) for (int i=a; i>=b; --i)

typedef long long int ll;

char buff[50];
int counts[26];
int main() {

  memset(counts, 0, sizeof counts);

  scanf("%s", buff);
  string password(buff);
  scanf("%s", buff);
  string message(buff);

  for (char c : password)
    counts[c-'A']++;

  int index = 0;
  bool success = true;
  for(char c : message) {
    if (counts[c-'A']) {
      if (password[index] != c) {
        success = false;
        break;
      }
      index++;
      counts[c-'A']--;
    }
  }  
  success &= (index == password.size());

  if (success)
    puts("PASS");
  else
    puts("FAIL");

  return 0;
}