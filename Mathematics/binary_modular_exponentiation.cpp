// compute a^b (mod m)
// use ll: with m ~ 1e9, a * a can reach ~1e18, which overflows int
ll binary_exp(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b&1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}
