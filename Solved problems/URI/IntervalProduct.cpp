// tags: segment tree, point update, range query
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
int N,K;

int get_sign(int x) {
    return (x > 0 ? 1 :(x < 0 ? -1 : 0));
}

struct {
    int arr[MAXN];
    int tree[4 * MAXN + 5];
    int leaf[MAXN];

    inline int left(int u) { return u << 1; }
    inline int right(int u) { return (u << 1) + 1; }

    void build(int u, int i, int j) {
        if (i == j) {
            leaf[i] = u;
            tree[u] = arr[i];
        } else {
            int lu = left(u), ru = right(u), m = (i+j)/2;
            build(lu, i, m);
            build(ru, m+1, j);
            tree[u] = get_sign(tree[lu] * tree[ru]);                
        }
    }

    void update(int i, int newval) {
        int sign = get_sign(newval);
        if (sign == arr[i])
            return;        
        int u = leaf[i];
        arr[i] = sign;
        tree[u] = sign;
        u >>= 1;
        while (u) {
            int lu = left(u), ru = right(u);
            sign = get_sign(tree[lu] * tree[ru]);
            if (sign == tree[u])
                break;
            tree[u] = sign;
            u >>= 1;
        }
    }

    int query(int a, int b, int u, int i, int j) {
        if (j < a or b < i)
            return 1;
        if (a <= i and j <= b)
            return tree[u];
        int lu = left(u), ru = right(u), m = (i+j)/2;
        return get_sign(query(a,b,lu,i,m) * query(a,b,ru,m+1,j));
    }

} st;

int main() {
    string line;
    while(scanf("%d%d", &N, &K)==2) {
        rep(i,0,N-1) {
            int x; scanf("%d", &x);
            st.arr[i] = get_sign(x);
        }
        st.build(1,0,N-1);
        getchar();
        while (K--) {            
            getline(cin, line);
            if (line[0] == 'C') {
                int i, v; sscanf(line.c_str() + 1, "%d%d", &i, &v); --i;
                st.update(i, v);
            } else {
                int a, b; sscanf(line.c_str() + 1, "%d%d", &a, &b); --a, --b;
                int sign = st.query(a,b,1,0,N-1);
                putchar(sign > 0? '+': (sign < 0? '-': '0'));
            }
        }
        puts("");
    }
    return 0;
}