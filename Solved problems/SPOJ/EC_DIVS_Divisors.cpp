// WARNING: gives TLE :s
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = 100000;

bool is_prime[MAXN+1];
void init_primes() {
    memset(is_prime, true, sizeof is_prime);
    is_prime[1] = false;
    int limit = (int)sqrt(MAXN);    
    rep(i,2,limit) {
        if (is_prime[i]) {
            for (int j=i*i; j <= MAXN; j+=i) {
                is_prime[j] = false;            
            }
        }
    }
}

int gcd(int a, int b) {
    int tmp;
    while (b) tmp = a, a = b, b = tmp % b;
    return a;
}

void print_nonprime_divisors(int x) {
    static umap<int,set<int>> cache;

    set<int>* divisors;
    auto it = cache.find(x);
    
    if (it == cache.end()) { // not in cache
        int limit = (int)sqrt(x);
        bool empty = true;
        cache[x] = set<int>();
        divisors = &cache[x];

        rep(a,1,limit) {
            if (x % a == 0) {
                int b = x / a;
                if (!is_prime[a]) divisors->insert(a);
                if (!is_prime[b]) divisors->insert(b);
            }
        }
    } else { // in cache
        divisors = &(it->second);        
    }

    if (divisors->size() > 0) {
        bool first = true;
        for (int x : *divisors) {
            if (first) {
                printf("%d", x);
                first = false;
            } else {
                printf(" %d", x);
            }
        }
        puts("");
    } else {        
        puts("-1");
    }
}

enum { ADD, REMOVE };

struct ST {
    int tree[MAXN * 4 + 5];
    int count[MAXN+1];
    int leaf[MAXN+1];

    int inline left(int u) { return u << 1; }
    int inline right(int u) { return (u << 1) + 1; }

    void build(int u, int i, int j) {
        if (i==j) {
            leaf[i] = u;
        } else {
            int lu = left(u), ru = right(u), m = (i+j)/2;
            build(lu, i, m);
            build(ru, m+1, j);
        }
    }

    void update(int x, int op) {
        bool dirty = false;
        if (op == ADD) {
            if (count[x]++ == 0) dirty = true;
        } else { // REMOVE
            if (count[x]-- == 1) dirty = true;
        }
        if (dirty) {
            int u = leaf[x];
            tree[u] = (count[x] > 0) ? x : 0;
            u >>= 1;
            while (u) {
                tree[u] = gcd(tree[left(u)], tree[right(u)]);
                u >>= 1;
            }
        }
    }
    
    void reset() {
        memset(tree, 0, sizeof tree);
        memset(count, 0, sizeof count);
    }

    ST() {}
};

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);  //debugging
    // puts("---- debug1");
    init_primes();
    // puts("---- debug2");
    ST* st = new ST();
    st->build(1,1,MAXN);
    // puts("---- debug3");
    int T; scanf("%d", &T);
    while (T--) {
        st->reset();
        int n; scanf("%d", &n);
        while (n--) {
            char buff[10];
            scanf("%s", buff);
            if (strcmp(buff, "UPD") == 0) { // update                
                int x;
                scanf("%s %d", buff, &x);
                if (strcmp(buff, "ADD") == 0) { // add
                    st->update(x, ADD);
                } else { // remove
                    st->update(x, REMOVE);                    
                }
            } else { // print
                print_nonprime_divisors(st->tree[1]);
            }
        }
    }
    return 0;
}