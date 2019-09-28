// references:
// http://www.cplusplus.com/reference/map/map/
// http://www.cplusplus.com/reference/map/multimap/
// ** SUMMARY **
//  same as set and multiset, except that for each key
//  now there is a value associated to it (if we only consider
//  the keys is the same as set/multiset)

//================
// INITIALIZATION
//================
// --- map
map<string,float> m {{"a",1.50}, {"b",2.10}, {"c",1.40}};
// or
map<string,float> m;
m.emplace("a", 1.50);
m.emplace("b", 2.10);
m.emplace("c", 1.40);
// --- multimap
// ** same as map

//=========
// INSERT
//=========
// --- map
map<char,int> m;
// first insert function version (single parameter):
m.insert( pair<char,int>('a',100) );
m.insert( pair<char,int>('z',200) );
auto ret = m.insert ( pair<char,int>('z',500) );
if (ret.second==false) {
    cout << "element 'z' already existed";
    cout << " with a value of " << ret.first->second << '\n';
}
// second insert function version (with hint position):
auto it = m.begin();
m.insert(it, pair<char,int>('b',300));  // max efficiency inserting
m.insert(it, pair<char,int>('c',400));  // no max efficiency inserting
// third insert function version (range insertion):
map<char,int> m2;
m2.insert(m.begin(), m.find('c'));
// showing contents:
cout << "m contains:\n";
for (auto& kv : m) cout << kv.first << " => " << kv.second << '\n';
cout << "m2 contains:\n";
for (auto& kv : m2) cout << kv.first << " => " << kv.second << '\n';
/*
element 'z' already existed with a value of 200
m contains:
a => 100
b => 300
c => 400
z => 200
m2 contains:
a => 100
b => 300
 */
// --- multimap
// ** same as map

//=================
// map::operator[]
//=================
map<char,string> m;
m['a']="an element";
m['b']="another element";
m['c']=m['b'];
cout << "m['a'] is " << m['a'] << '\n';
cout << "m['b'] is " << m['b'] << '\n';
cout << "m['c'] is " << m['c'] << '\n';
cout << "m['d'] is " << m['d'] << '\n'; // ('d' -> "") is created by default
cout << "m now contains " << m.size() << " elements.\n";
/* 
m['a'] is an element
m['b'] is another element
m['c'] is another element
m['d'] is
m now contains 4 elements.
*/

//=================
// map::operator=
//=================
map<char,int> first;
map<char,int> second;
first['x']=8;
first['y']=16;
first['z']=32;
second=first;           // second now contains 3 ints
first=map<char,int>();  // and first is now empty
cout << "Size of first: " << first.size() << '\n';
cout << "Size of second: " << second.size() << '\n';

//=========================
// generating ids with map
//=========================
int get_id(string& name) {
    static int id = 0;
    static map<string,int> name2id;
    auto it = name2id.find(name);
    if (it == name2id.end())
        return name2id[name] = id++;
    return it->second;
}