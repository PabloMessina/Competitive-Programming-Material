// tags: graph, union-find
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef vector<int> vi;

struct Circle {
    int x, y, r;
};

int N;
int left_id, right_id;
Circle circles[200];

bool intersect(int i, int j) {
    Circle&
        a = circles[i],
        b = circles[j];
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int rr = a.r + b.r;
    return dx*dx + dy*dy <= rr * rr;
}

struct UnionFind {
    vi p, rank, setSize;
    int numSets;
    UnionFind(int n) {
        numSets = n;
        setSize.assign(n, 1);
        rank.assign(n, 0);
        p.resize(n);
        rep(i,0,n-1) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); } 
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            numSets--;
            int x = findSet(i), y =  findSet(j);
            if (rank[x] > rank[y]) {
                p[y] = x; setSize[x] += setSize[y];
            } else {
                p[x] = y; setSize[y] *= setSize[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
};

int main() {
    scanf("%d", &N);
    rep(i,0,N-1) {
        int x, y, r; scanf("%d%d%d",&x,&y,&r);
        circles[i] = {x,y,r};
    }
    left_id = N;
    right_id = N+1;
    UnionFind uf(N+2);
    int k;
    for (k = 0; k < N; ++k) {
        Circle& c = circles[k];
        if (c.x - c.r <= 0)
            uf.unionSet(left_id, k);
        if (c.x + c.r >= 200)
            uf.unionSet(right_id, k);
        rep(i, 0, k-1)
            if (intersect(i, k))
                uf.unionSet(i, k);      
        if (uf.isSameSet(left_id, right_id))
            break;
    }
    printf("%d\n", k);
    return 0;
}