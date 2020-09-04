// tags: implementation
#include <bits/stdc++.h>
using namespace std;
// -------------------------------
map<string,int> word2val;
map<int,string> val2word;
int main() {
    string line;
    while (getline(cin, line)) {        
        stringstream ss;
        ss << line;
        string command;
        ss >> command;
        if (command == "clear") {
            word2val.clear();
            val2word.clear();
        } else if (command == "def") {
            string w;
            int v;
            ss >> w >> v;
            if (word2val.count(w)) {
                val2word.erase(word2val[w]);
            }
            word2val[w] = v;
            val2word[v] = w;
        } else {
            assert (command == "calc"); // paranoico
            string w, op;
            ss >> w;
            int ans = 0;
            bool valid = true;
            if (word2val.count(w) == 0) { // not found
                valid = false;
            } else {
                ans = word2val[w];
            }
            while (valid and (ss >> op >> w)) {
                if (word2val.count(w) == 0) {// not found
                    valid = false;
                    break;
                }
                if (op == "+") ans += word2val[w];
                else ans -= word2val[w];
            }
            cout << line.substr(5) << " ";
            if (valid) {
                auto it = val2word.find(ans);
                if (it == val2word.end()) {
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