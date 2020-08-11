// tags: math, rational root theorem, arithmetic parser, implementation,
// modular arithmetics
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;

const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;

vector<int> get_divisors(int x) {
    vector<int> divs;
    rep(d,1,x) {
        if (d*d > x) break;
        if (x % d == 0) {
            divs.push_back(d);
            divs.push_back(x/d);
        }
    }
    return divs;
}

struct Poly {
    vector<int> coefs;
    int degree;
    Poly(const string& s, int start, int len) {
        invrep(i,len-1,0) coefs.push_back(s[i+start] - '0');
        degree = coefs.size() - 1;
    }
    void trim() {
        while(degree > 0 and coefs[degree] == 0) degree--;
        coefs.resize(degree + 1);
    }
    Poly& operator*=(const Poly& rhs) {
        vector<int> new_coefs(degree + rhs.degree + 1, 0);
        rep(i,0,degree) {
            rep(j,0,rhs.degree) {
                new_coefs[i+j] += coefs[i] * rhs.coefs[j];
            }
        }
        this->coefs = new_coefs;
        this->degree = new_coefs.size() - 1;
        trim();
        return *this;
    }
    Poly& operator+=(const Poly& rhs) {
        int new_degree = max(degree, rhs.degree);               
        vector<int> new_coefs = coefs;
        new_coefs.resize(new_degree+1, 0);
        rep(i,0,rhs.degree) new_coefs[i] += rhs.coefs[i];
        this->coefs = new_coefs;
        this->degree = new_degree;
        trim();
        return *this;
    }
    Poly& operator-=(const Poly& rhs) {
        int new_degree = max(degree, rhs.degree);               
        vector<int> new_coefs = coefs;
        new_coefs.resize(new_degree+1, 0);
        rep(i,0,rhs.degree) new_coefs[i] -= rhs.coefs[i];
        this->coefs = new_coefs;
        this->degree = new_degree;
        trim();
        return *this;
    }
    void remove_zero_roots() {
        if (degree == 0) return;
        int i = 0;
        while (coefs[i] == 0) i++;
        rep(j,i,degree) coefs[j-i] = coefs[j];
        degree -= i;
        coefs.resize(degree+1);
    }
    void remove_gcd() {
        if (degree == 0 and coefs[0] == 0) return;
        int g = 0;
        for (int c : coefs) g = __gcd(g, abs(c));
        for (int& c : coefs) c /= g;
    }
    ll eval(ll base, ll mod) {
        ll ans = 0;
        invrep(i, degree, 0) {
            ans = (ans * base) % mod;
            ans = (ans + (ll)coefs[i]) % mod;
        }
        return ans;
    }
    void print_integer_roots(int min_base) {
        remove_zero_roots();
        remove_gcd();
        if (degree == 0) {
            if (coefs[0] == 0) cout << min_base << "+\n";
            else cout << "*\n";
        } else {
            set<int> bases;
            vector<int> divs0 = get_divisors(abs(coefs[0]));
            for (int d : divs0) {
                if (d < min_base) continue;
                if (eval(d, MOD1) == 0 and eval(d, MOD2) == 0) {
                    bases.insert(d);
                }
            }
            if (bases.size() > 0) {
                int i = 0;
                for (int b : bases) {
                    if (i++ > 0) cout << " ";
                    cout << b;
                }
                cout << '\n';
            } else {
                cout << "*\n";
            }            
        }
    }
};

bool is_digit(char c) { return '0' <= c and c <= '9'; }

Poly parse_poly(string& s, int& offset) {
    int start = offset;
    while (offset < s.size() and is_digit(s[offset])) offset++;
    return Poly(s, start, offset-start);
}

Poly parse_mult(string& s, int& offset) {
    Poly pol = parse_poly(s, offset);
    while (offset < s.size() and s[offset] == '*') {
        pol *= parse_poly(s, ++offset);
    }
    return pol;
}

Poly parse_sum(string& s, int& offset) {
    Poly pol = parse_mult(s, offset);
    while (offset < s.size() and s[offset] == '+') {
        pol += parse_mult(s, ++offset);
    }
    return pol;
}

Poly parse_equation(string& s) {
    int offset = 0;
    Poly pol = parse_sum(s, offset);
    pol -= parse_sum(s, ++offset);
    return pol;
}

int min_base(string& s) {
    int b = 2;
    for (char c : s) if (is_digit(c)) b = max(b, c-'0'+1);
    return b;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    while(1) {
        string line; cin >> line;
        if (line.size() == 1) break;
        Poly pol = parse_equation(line);
        pol.print_integer_roots(min_base(line));
    }
    return 0;
}