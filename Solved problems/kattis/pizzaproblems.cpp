// tags: random walk, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXM = 250;
int N, M;
mt19937 rng;

int rand_int(int a, int b) {
    return uniform_int_distribution<int>(a, b)(rng);
}

struct Person {
    vector<bool> wishes;
    vector<int> unsat_wishes;
    vector<pair<int,bool>> wish_list;
    vector<int> i2idx;
    Person() {
        wishes.assign(MAXM, false);
        i2idx.assign(MAXM, -1);
        wish_list.reserve(MAXM);
        unsat_wishes.reserve(MAXM);
    }
    void add_wish(int i, bool val) {
        wish_list.emplace_back(i, val);
        wishes[i] = val;
    }
    void notify_change(int i, bool val) {
        bool sat = wishes[i] == val;
        if (sat) {
            if (i2idx[i] != -1) {
                unsat_wishes[i2idx[i]] = unsat_wishes.back();
                i2idx[unsat_wishes.back()] = i2idx[i];
                i2idx[i] = -1;
                unsat_wishes.pop_back();
            }
        } else {
            i2idx[i] = unsat_wishes.size();
            unsat_wishes.push_back(i);
        }
    }
    bool ok() {
        int tot_wishes = wish_list.size();
        int sat_count = tot_wishes - unsat_wishes.size();
        return sat_count * 3 > tot_wishes;
    }
    int get_unsatisfied_wish() {
        // return unsat_wishes[rand() % unsat_wishes.size()];
        return unsat_wishes[rand_int(0, unsat_wishes.size()-1)];
    }
};

map<string, int> name2id;
vector<string> id2name;
int get_id(const string& name) {    
    auto it = name2id.find(name);
    if (it == name2id.end()) {
        id2name.push_back(name);
        return name2id[name] = id2name.size() - 1;
    }
    return it->second;
}

struct Ingredient {
    bool used = true;
    vector<int> people;
};

struct SAT {
    vector<int> unsat_people;
    vector<int> i2idx;
    SAT(int n) {
        i2idx.assign(n, -1);
    }
    void notify_change(int i, bool sat) {
        if (sat and i2idx[i] != -1) {
            unsat_people[i2idx[i]] = unsat_people.back();
            i2idx[unsat_people.back()] = i2idx[i];
            i2idx[i] = -1;
            unsat_people.pop_back();
        } else if (not sat and i2idx[i] == -1) {
            i2idx[i] = unsat_people.size();
            unsat_people.push_back(i);
        }
    }
    bool ok() { return unsat_people.empty(); }
    int get_unsatisfied_person() {
        // return unsat_people[rand() % unsat_people.size()];
        return unsat_people[rand_int(0, unsat_people.size()-1)];        
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());

    cin >> N;
    vector<Person> people(N);
    vector<Ingredient> ingredients(MAXM);
    rep(i,0,N) {
        int w; cin >> w;
        rep(j,0,w) {
            string token; cin >> token;
            bool val = token[0] == '+';
            int id = get_id(token.substr(1));
            people[i].add_wish(id, val);
            ingredients[id].people.push_back(i);
        }
    }
    M = name2id.size();
    ingredients.resize(M);
    SAT sat(N);
    rep(i,0,M) {
        auto& ing = ingredients[i];
        ing.used = rand_int(0, 1);
        for (int p : ing.people) {
            people[p].notify_change(i, ing.used);
            sat.notify_change(p, people[p].ok());
        }
    }
    while (not sat.ok()) {
        int p = sat.get_unsatisfied_person();
        int i = people[p].get_unsatisfied_wish();
        auto& ing = ingredients[i];
        ing.used ^= 1;
        for (int j : ing.people) {
            people[j].notify_change(i, ing.used);
            sat.notify_change(j, people[j].ok());
        }
    }
    rep(i, 0, M) {
        auto& ing = ingredients[i];
        if (ing.used) cout << id2name[i] << '\n';
    }
    return 0;
}