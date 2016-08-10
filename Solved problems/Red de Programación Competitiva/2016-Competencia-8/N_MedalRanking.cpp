#include <cstdio>
using namespace std;

int main() {
  int n;
  scanf("%d", &n);
  while(n--) {
    int g1, s1, b1, g2, s2, b2;
    scanf("%d%d%d%d%d%d",&g1,&s1,&b1,&g2,&s2,&b2);
    bool color = (g1>g2 || 
      (g1 == g2 && (s1 > s2 || (s1 == s2 && b1 > b2))));
    bool count = g1 + s1 + b1 > g2 + s2 + b2;
    printf("%d %d %d %d %d %d\n",g1,s1,b1,g2,s2,b2);
    if (color && count)
      puts("both");
    else if(color)
      puts("color");
    else if(count)
      puts("count");
    else
      puts("none");
  }
  return 0;
}