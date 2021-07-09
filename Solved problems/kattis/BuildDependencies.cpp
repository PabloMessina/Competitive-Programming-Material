// tags: toposort, DAGs, graphs, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
// -------------------------------
const int MAXN = 100000;
int N;
vector<vector<int>> g;

int ID = 0;
umap<string,int> name2id;
vector<string> names;
int get_id(string& s) {
    auto it = name2id.find(s);
    if (it == name2id.end()) {
        names[ID] = s;
        return name2id[s] = ID++;
    }
    return it->second;
}

vector<int> toposorted;
bool visited[MAXN];
void dfs(int u) {
    visited[u] = true;
    for (int v : g[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
    toposorted.push_back(u);
}
void topo_sort(int start) {
    memset(visited, 0, sizeof(bool) * N);
    dfs(start);
    invrep(i, toposorted.size()-1, 0) {
        cout << names[toposorted[i]] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    g.resize(N);
    names.resize(N);
    string line; 
    getline(cin, line);
    rep(i,0,N) {
        getline(cin, line);
        stringstream ss(line);
        string token;
        ss >> token;
        // token.pop_back(); // quizás funciona
        token = token.substr(0, token.size()-1);
        int u = get_id(token);
        while (ss >> token) {
            int v = get_id(token);
            g[v].push_back(u);
        }
    }
    assert (N == ID);
    string query; cin >> query;
    int qid = get_id(query);
    toposorted.reserve(N);
    topo_sort(qid);
    return 0;
}