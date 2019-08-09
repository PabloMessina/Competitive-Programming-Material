// references:
// http://www.cplusplus.com/reference/unordered_map/unordered_map/
// http://www.cplusplus.com/reference/unordered_map/unordered_multimap/
// ** SUMMARY **
//  same as unordered_set and unordered_multiset, except that for each key
//  now there is a value associated to it (if we only consider
//  the keys is the same as unordered_set/unordered_multiset)

//================
// INITIALIZATION
//================
// --- unordered_map
unordered_map<string,float> m {{"a",1.50}, {"b",2.10}, {"c",1.40}};
// or
unordered_map<string,float> m;
m.emplace("a", 1.50);
m.emplace("b", 2.10);
m.emplace("c", 1.40);
// --- unordered_multimap
// ** same as unordered_map

//=========
// INSERT
//=========
// --- unordered_map
unordered_map<string,double>
            myrecipe,
            mypantry = {{"milk",2.0},{"flour",1.5}};
pair<string,double> myshopping("baking powder",0.3);
myrecipe.insert(myshopping);                       // copy insertion
myrecipe.insert(make_pair("eggs",6.0));            // move insertion
myrecipe.insert(mypantry.begin(), mypantry.end()); // range insertion
myrecipe.insert( {{"sugar",0.8},{"salt",0.1}} );   // initializer list insertion
cout << "myrecipe contains:" << '\n';
for (auto& x: myrecipe) cout << x.first << ": " << x.second << '\n';
cout << '\n';/*
myrecipe contains:
salt: 0.1
eggs: 6
sugar: 0.8
baking powder: 0.3
flour: 1.5
milk: 2 */
// --- unordered_multimap
// ** same as unordered_map

//==========================
// unordered_map::operator[]
//===========================
unordered_map<string,string> m;
m["Bakery"]="Barbara";  // new element inserted
m["Seafood"]="Lisa";    // new element inserted
m["Produce"]="John";    // new element inserted
string name = m["Bakery"];   // existing element accessed (read)
m["Seafood"] = name;         // existing element accessed (written)
m["Bakery"] = m["Produce"];  // existing elements accessed (read/written)
name = m["Deli"];      // non-existing element: new element "Deli" inserted!
m["Produce"] = m["Gifts"];    // new element "Gifts" inserted, "Produce" written
for (auto& x: m) cout << x.first << ": " << x.second << '\n';
/*
Seafood: Barbara
Deli:
Bakery: John
Gifts:
Produce:
*/

//==========================
// unordered_map::operator=
//==========================
typedef unordered_map<string,string> stringmap;
stringmap merge (stringmap a,stringmap b) {
    stringmap temp(a); temp.insert(b.begin(),b.end()); return temp;
}
int main() {
    stringmap first, second, third;
    first = {{"AAPL","Apple"},{"MSFT","Microsoft"}};  // init list
    second = {{"GOOG","Google"},{"ORCL","Oracle"}};   // init list
    third = merge(first,second);                      // move
    first = third;                                    // copy
    cout << "first contains:";
    for (auto& x: first) cout << " " << x.first << ":" << x.second;
    cout << '\n';
    return 0;
}
// first contains: MSFT:Microsoft AAPL:Apple GOOG:Google ORCL:Oracle
