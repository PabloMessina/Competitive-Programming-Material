int mod_pow(int b, int e, int m) {
  if (e == 1)
    return b % m;
  int he = e / 2;
  int x = mod_pow(b, he, m);
  x = (x * x) % m;
  if (e % 2 == 1)
    x = (x * b) % m;
  return x;
}