#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int wins = 0;
int stars = 0;
int prank = 25;
int rank_stars[26];

void update_state(char c) {
  if (c == 'W') { // win
    stars++;
    wins++;
    if (6 <= prank && prank <= 25) {
      if (wins >= 3) stars++;
    }
    if (prank >= 1) {
      if (stars > rank_stars[prank]) {
        stars -= rank_stars[prank];
        prank--;
      }
    }
  } else { // lose
    wins = 0;
    if (1 <= prank && prank <= 20) {
      stars--;
      if (stars < 0) {
        if (prank == 20) {
          stars = 0;
        } else {
          prank++;
          stars = rank_stars[prank] - 1;
        }
      }
    }
  }
}

int main() {

  rep(i,21,25) rank_stars[i] = 2;
  rep(i,16,20) rank_stars[i] = 3;
  rep(i,11,15) rank_stars[i] = 4;
  rep(i,1,10) rank_stars[i] = 5;

  string input;
  getline(cin, input);
  for (char c : input ) {
    update_state(c);
  }
  if (prank == 0)
    puts("LEGEND");
  else
    printf("%d\n", prank);
  return 0;
}