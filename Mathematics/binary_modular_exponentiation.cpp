// compute a^b (mod m)
int binary_exp(int a, int b, int m) {
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b&1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}