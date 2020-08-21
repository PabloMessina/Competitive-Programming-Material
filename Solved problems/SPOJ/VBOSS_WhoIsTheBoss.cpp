// tags: sorting, ordered sets (std::set), top-down DP,
// graphs, trees
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
// -------------------------------

const int MAXM = 30000;

struct Employee {
    int ID, salary, height;
    bool operator<(const Employee& o) const {
        return tie(height, salary) < tie(o.height, o.salary);
    }
} employees[MAXM];
int parent[MAXM];
vector<int> children[MAXM];

int memo[MAXM];
int count_descendants(int i) { // top-down dp
    if (memo[i] != -1) return memo[i];
    int count = children[i].size();
    for (int j : children[i]) count += count_descendants(j);
    return memo[i] = count;
}
int get_parent(int i) {
    if (parent[i] == -1) return 0;
    return employees[parent[i]].ID;
}

bool salary_cmp(int i, int j) {
    return employees[i].salary < employees[j].salary;
}

int main() {
    // read input
    int n; cin >> n;
    while (n--) {
        int m, q; cin >> m >> q;
        rep(i,0,m) {
            Employee& e = employees[i];
            cin >> e.ID >> e.salary >> e.height;
            children[i].clear();
        }
        // sort employees lexicographically
        sort(employees, employees + m);
        // map IDs to indexes
        umap<int,int> id2index;
        rep(i,0,m) id2index[employees[i].ID] = i;
        // find immediate boss for each employee
        // reference: https://stackoverflow.com/questions/2620862/using-custom-stdset-comparator
        set<int, decltype(salary_cmp)*> active(salary_cmp);
        active.insert(m-1);
        parent[m-1] = -1;
        invrep(i, m-2, 0) {
            auto ret = active.insert(i);
            int b = *std::next(ret.first);
            parent[i] = b;
            children[b].push_back(i);
        }
        // answer queries
        memset(memo, -1, sizeof(int) * m);
        while (q--) {
            int id; cin >> id;
            int i = id2index[id];
            cout << get_parent(i) << " "
                 << count_descendants(i) << '\n';
        }
    }
    return 0;
}