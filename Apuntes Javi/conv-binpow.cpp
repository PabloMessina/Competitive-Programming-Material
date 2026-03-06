// usar con template de ntt

vec<ll> conv_binpow(vec<ll> a, ll b) {
    vec<ll> res = {1};
    while (b > 0) {
        if (b & 1)
            res = conv(res, a);
        a = conv(a, a);
        b >>= 1;
    }
    return res;
}
