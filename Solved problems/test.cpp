#include <bits/stdc++.h>
using namespace std;

int reverse_bits(int x) {
  int v = 0;
  while (x) v <<= 1, v |= x&1, x >>= 1;
  return v;
}

string bitstring(int x) {
  int len = sizeof(x) * 8 - __builtin_clz(x);
  if (len == 0) return "0";

  char buff[len+1]; buff[len] = '\0';
  for (int i = len-1; i >= 0; --i, x >>= 1)
    buff[i] = (char)('0' + (x&1));
  return string(buff);
}

int main() {
  while (true) {
    int n; scanf("%d", &n);
    string sbef = bitstring(n);
    string saft = bitstring(reverse_bits(n));
    printf("bef = %s, aft = %s\n", sbef.c_str(), saft.c_str());
  }
}