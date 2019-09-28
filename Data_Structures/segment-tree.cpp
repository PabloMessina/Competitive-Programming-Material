#include <bits/stdc++.h>
using namespace std;

//=============================
// 1) Segment Tree - ITERATIVE
//=============================
// source: https://docs.google.com/document/d/1rcex_saP4tExbbU62qGUjR3eenxOh-50i9Y45WtHkc4/
/* 
Se requiere un struct para el nodo (ej: prodsgn).
Un nodo debe tener tres constructores:
    Aridad 0: Construye el neutro de la operacion
    Aridad 1: Construye un nodo hoja a partir del input
    Aridad 2: Construye un nodo segun sus dos hijos

Construccion del segment tree:
    Hacer un arreglo de nodos (usar ctor de aridad 1).
    ST<miStructNodo> miSegmentTree(arregloDeNodos);
Update:
    miSegmentTree.set_point(indice, miStructNodo(input));
Query:
    miSegmentTree.query(l, r) es inclusivo exclusivo y da un nodo. Usar la info del nodo para obtener la respuesta.
 */
template<class node> struct ST {
    vector<node> t; int n;
    ST(vector<node> &arr) {
        n = arr.size();
        t.resize(n*2);
        copy(arr.begin(), arr.end(), t.begin() + n);
        for (int i = n-1; i > 0; --i)
            t[i] = node(t[i<<1], t[i<<1|1]);
    }
    // 0-indexed
    void set_point(int p, const node &value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p>>1] = node(t[p], t[p^1]);
    }
    // inclusive exclusive, 0-indexed
    node query(int l, int r) {
        node ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = node(ansl, t[l++]);
            if (r&1) ansr = node(t[--r], ansr);
        }
        return node(ansl, ansr);
    }
};

// Interval Product (LiveArchive)
struct prodsgn {
    int sgn;
    prodsgn() {sgn = 1;}
    prodsgn(int x) { sgn = (x > 0) - (x < 0); }
    prodsgn(const prodsgn &a, const prodsgn &b) { sgn = a.sgn*b.sgn; }
};

// Maximum Sum (SPOJ)
struct maxsum {
    int first, second;
    maxsum() {first = second = -1;}
    maxsum(int x) { first = x; second = -1; }
    maxsum(const maxsum &a, const maxsum &b) {
        if (a.first > b.first) {
            first = a.first;
            second = max(a.second, b.first);
        } else {
            first = b.first; second = max(a.first, b.second);
        }
    }
    int answer() { return first + second; }
};

// Range Minimum Query
struct rminq {
    int value;
    rminq() {value = INT_MAX;}
    rminq(int x) {value = x;}
    rminq(const rminq &a, const rminq &b) {
        value = min(a.value, b.value);
    }
};

//=============================
// 2) Segment Tree - RECURSIVE
//=============================

template<class t> class ST {
    vector<ll> *arr, st; int n;

    void build(int u, int i, int j) {
        if (i == j) {
            st[u] = (*arr)[i];
            return;
        }
        int m = (i+j)/2, l = u*2+1, r = u*2+2;
        build(l, i, m);
        build(r, m+1, j);
        st[u] = t::merge_op(st[l], st[r]);
    }

    ll query(int a, int b, int u, int i, int j) {
        if (j < a or b < i) return t::neutro;
        if (a <= i and j <= b) return st[u];
        int m = (i+j)/2, l = u*2+1, r = u*2+2;
        ll x = query(a, b, l, i, m);
        ll y = query(a, b, r, m+1, j);
        return t::merge_op(x, y);
    }

    void update(int a, ll value, int u, int i, int j) {
        if (j < a or a < i) return;
        if (i == j) st[a] += value;
        else {
            int m = (i+j)/2, l = u*2+1, r = u*2+2;
            update(a, value, l, i, m);
            update(a, value, r, m+1, j);
            st[u] = t::merge_op(st[l], st[r]);
        }
    }

public:
    ST(vector<ll>& v) {
        arr = &v;
        n = v.size();
        st.resize(n*4+5);
        build(0, 0, n-1);
    }

    ll query(int a, int b) {
        return query(a, b, 0, 0, n-1);
    }

    void update(int a, ll value) {
        update(a, value, 0, 0, n-1);
    }
};

struct RSQ { // range sum query
    static ll const neutro = 0;
    static ll merge_op(ll x, ll y) { return x + y; }
};

struct RMinQ { // range minimun query
    static ll const neutro = LLONG_MAX;
    static ll merge_op(ll x, ll y) { return min(x, y); }
};

struct RMaxQ { // range maximum query
    static ll const neutro = LLONG_MIN;
    static ll merge_op(ll x, ll y) { return max(x, y); }
};

// usage
int main() {
    vector<int> A = { 18, 17, 13, 19, 15, 11, 20 };
    ST<RSQ> stl(A);
    stl.update(2, 100);
    stl.query(1, 3);
    return 0;
}