/*
 *Description:* Segment tree but with range updates, build $O(n)$, query and update $O(log n)$
 *Status:* Highly tested
*/
template<
  class T1, // answer value stored on nodes
  class T2, // lazy update value stored on nodes
  T1 merge(T1, T1), 
  void pushUpd(T2& /*parent*/, T2& /*child*/, int, int, int, int), // push update value from a node to another. parent -> child
  void applyUpd(T2&, T1&, int, int)           // apply the update value of a node to its answer value. upd -> ans
>
struct segment_tree_lazy{
  vector<T1> ST; vector<T2> lazy; vector<bool> upd;
  int n;
  void build(int i, int l, int r, vector<T1>&values){
    if (l == r){
      ST[i] = values[l];
      return;
    }
    build(i << 1, l, (l + r) >> 1, values);
    build(i << 1 | 1, (l + r) / 2 + 1, r, values);
    ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
  }
  segment_tree_lazy() {}
  segment_tree_lazy(vector<T1>&values){
    n = values.size(); ST.resize(n << 2 | 3);
    lazy.resize(n << 2 | 3); upd.resize(n << 2 | 3, false);
    build(1, 0, n - 1, values);
  }
  void push(int i, int l, int r){
    if (upd[i]){
      applyUpd(lazy[i], ST[i], l, r);
      if (l != r){
        pushUpd(lazy[i], lazy[i << 1], l, r, l, (l + r) / 2);
        pushUpd(lazy[i], lazy[i << 1 | 1], l, r, (l + r) / 2 + 1, r);
        upd[i << 1] = 1;
        upd[i << 1 | 1] = 1;
      }
      upd[i] = false;
      lazy[i] = T2();
    }
  }
  void update(int i, int l, int r, int a, int b, T2 &u){
    if (l >= a and r <= b){
      pushUpd(u, lazy[i], a, b, l, r);
      upd[i] = true;
    }
    push(i, l, r);
    if (l > b or r < a) return;
    if (l >= a and r <= b) return;
    update(i << 1, l, (l + r) >> 1, a, b, u);
    update(i << 1 | 1, (l + r) / 2 + 1, r, a, b, u);
    ST[i] = merge(ST[i << 1], ST[i << 1 | 1]);
  }
  void update(int a, int b, T2 u){
    if (a > b){
      update(0, b, u);
      update(a, n - 1, u);
      return ;
    }
    update(1, 0, n - 1, a, b, u);
  }
  T1 query(int i, int l, int r, int a, int b){
    push(i, l, r);
    if (a <= l and r <= b)
      return ST[i];
    int mid = (l + r) >> 1;
    if (mid < a)
      return query(i << 1 | 1, mid + 1, r, a, b);
    if (mid >= b) 
      return query(i << 1, l, mid, a, b);
    return merge(query(i << 1, l, mid, a, b), query(i << 1 | 1, mid + 1, r, a, b));
  }
  T1 query(int a, int b){
    if (a > b) return merge(query(a, n - 1), query(0, b));
    return query(1, 0, n - 1, a, b);
  }
};



// To use it, you must define:
//   1. merge(T1 a, T1 b) → combina dos nodos hijos en un valor padre
//   2. pushUpd(T2 &parent, T2 &child, int l1, int r1, int l2, int r2) → 
//      propaga la actualización del nodo padre al hijo
//   3. applyUpd(T2 &upd, T1 &ans, int l, int r) → aplica el valor lazy (T2) 
//      al valor del nodo (T1)
//
/*
Cuando uses esta plantilla, necesitas proveer 3 funciones:
merge(T1 a, T1 b)
Define cómo combinar los valores de dos hijos.
Ejemplo: para un segmento que guarda sumas → return a + b;
pushUpd(T2 &parent, T2 &child, int Lp, int Rp, int Lc, int Rc)
Define cómo se transmite una actualización pendiente de un nodo a sus hijos.
Ejemplo: si las actualizaciones son aditivas → child += parent;
applyUpd(T2 &upd, T1 &node, int l, int r)
Define cómo aplicar una actualización a un nodo.
Ejemplo: para suma → node += (r - l + 1) * upd;
*/
//ejemplo suma acum

long long merge(long long a, long long b){ return a + b; }

void pushUpd(long long &p, long long &c, int Lp, int Rp, int Lc, int Rc){
  c += p; // suma acumulativa
}

void applyUpd(long long &u, long long &node, int l, int r){
  node += (r - l + 1) * u;
}


//ej uso
vector<long long> v = {1, 2, 3, 4, 5};
segment_tree_lazy<long long, long long, merge, pushUpd, applyUpd> st(v);

st.update(1, 3, 2LL);  // sumar 2 al rango [1, 3]
cout << st.query(0, 4); // suma total

