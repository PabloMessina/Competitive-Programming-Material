#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,a,b) for (int i=a; i>=b; --i)

const char* digits[10] = {
  "+---+"
  "|   |"
  "|   |"
  "+   +"
  "|   |"
  "|   |"
  "+---+",
  "    +"
  "    |"
  "    |"
  "    +"
  "    |"
  "    |"
  "    +",
  "+---+"
  "    |"
  "    |"
  "+---+"
  "|    "
  "|    "
  "+---+",
  "+---+"
  "    |"
  "    |"
  "+---+"
  "    |"
  "    |"
  "+---+",
  "+   +"
  "|   |"
  "|   |"
  "+---+"
  "    |"
  "    |"
  "    +",
  "+---+"
  "|    "
  "|    "
  "+---+"
  "    |"
  "    |"
  "+---+",
  "+---+"
  "|    "
  "|    "
  "+---+"
  "|   |"
  "|   |"
  "+---+",
  "+---+"
  "    |"
  "    |"
  "    +"
  "    |"
  "    |"
  "    +",
  "+---+"
  "|   |"
  "|   |"
  "+---+"
  "|   |"
  "|   |"
  "+---+",
  "+---+"
  "|   |"
  "|   |"
  "+---+"
  "    |"
  "    |"
  "+---+"
};

char answer[7][29];

void write_digit(int d, int offset) {
  const char* digit = digits[d];
  rep(r,0,6) rep(c,0,4)
    answer[r][offset + c] = digit[r * 5 + c];
}

int main() {
  int a,b,c,d;
  string line;

  memset(answer, ' ', sizeof answer);
  answer[2][14] = 'o';
  answer[4][14] = 'o';

  while (true) {
    getline(cin, line);
    if (line == "end") {
      puts("end");
      break;
    }
    a = line[0] - '0';
    b = line[1] - '0';
    c = line[3] - '0';
    d = line[4] - '0';

    // puts("--------------------");
    // printf("line = %s\n", line.c_str());
    // printf("%d%d:%d%d\n",a,b,c,d);

    write_digit(a, 0);
    write_digit(b, 7);
    write_digit(c, 17);
    write_digit(d, 24);

    rep(r,0,6) printf("%.*s\n", 29, answer[r]);
    puts("");
    puts("");
  }
  return 0;
}