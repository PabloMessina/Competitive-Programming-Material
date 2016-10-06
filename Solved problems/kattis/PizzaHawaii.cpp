#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,a,b) for (int i=a; i>=b; --i)

typedef long long int ll;
int T, N;

map<string,ll> foreign;
map<string,ll> native;
map<string,int> pizzaIds;
const ll bit = 1;
char buff[200];

void updateMap(map<string,ll>& m, string& key, int index) {
  auto it = m.find(key);
  ll val = (it == m.end()) ? 0 : it->second;
  val |= (bit << index);
  m[key] = val;
}

int getPizzaId(string& name, int& id) {
  auto it = pizzaIds.find(name);
  if (it == pizzaIds.end())
    return pizzaIds[name] = id++;
  return it->second;
}

int main() {
  scanf("%d", &T);
  rep(test,1,T) {

    foreign.clear();
    native.clear();

    if (test > 1)
      puts("\n");

    int id = 0;

    scanf("%d", &N);
    while(N--) {

      scanf("%s", buff);
      string name(buff);
      int pizzaId = getPizzaId(name, id);

      int m;

      scanf("%d", &m);
      while(m--) {
        scanf("%s", buff);
        string key(buff);
        updateMap(foreign, key, pizzaId);
      }

      scanf("%d", &m);
      while(m--) {
        scanf("%s", buff);
        string key(buff);
        updateMap(native, key, pizzaId);
      }
    }

    bool first = true;
    for(auto& i : foreign) {
      for(auto& j : native) {
        if (i.second == j.second) {
          if (first) first = false;
          else puts("");
          printf("(%s, %s)", i.first.c_str(), j.first.c_str());
        }
      }
    }
  }
  return 0;
}