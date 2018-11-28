// tags: implementation, string handling
#include <bits/stdc++.h> // import everything in one shot
using namespace std;

map<string,int> var2val;
map<int,string> val2var;

int main() {
    string line;
    while (getline(cin, line)) {        
        stringstream ss;
        ss << line;
        string command;
        ss >> command;
        if (command == "clear") {
            var2val.clear();
            val2var.clear();
        } else if (command == "def") {
            string var;
            int val;
            ss >> var >> val;
            auto it = var2val.find(var);
            if (it != var2val.end()) {
                val2var.erase(it->second);
            }
            var2val[var] = val;
            val2var[val] = var;
        } else {
            assert (command == "calc");
            string var, op;
            ss >> var;
            int ans = 0;
            bool valid = true;
            auto it = var2val.find(var);
            if (it == var2val.end()) { // not found
                valid = false;
            } else {
                ans = it->second;
            }
            while (valid and (ss >> op >> var)) {
                auto it = var2val.find(var);
                if (it == var2val.end()) { // not found
                    valid = false;
                    break;
                }
                if (op == "+") ans += it->second;
                else ans -= it->second;
            }
            cout << line.substr(5) << " ";
            if (valid) {
                auto it = val2var.find(ans);
                if (it == val2var.end()) {
                    cout << "unknown\n";                    
                } else {
                    cout << it->second << '\n';
                }
            } else {
                cout << "unknown\n";
            }
        }
    }
    return 0;
}