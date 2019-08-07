// references:
// http://www.cplusplus.com/reference/unordered_set/unordered_set/
// http://www.cplusplus.com/reference/unordered_set/unordered_multiset/
// ** unordered_multiset is basically the same as unordered_set
//    except that unordered_multiset allows duplicate elements

//=========
// RESERVE
//=========
unordered_set<string> s;
s.reserve(5);
s.insert("office");
s.insert("house");
s.insert("gym");
s.insert("parking");
s.insert("highway");
cout << "s contains:";
for (const string& x: s) cout << " " << x;
cout << '\n'; // s contains: highway house office gym parking
// By calling reserve with the size we expected for the unordered_set
// container we avoided the multiple rehashes that the increases in container
// size could have produced and optimized the size of the hash table.

//========
// INSERT
//========
unordered_set<string> s = {"yellow","green","blue"};
array<string,2> arr = {"black","white"};
string mystring = "red";
s.insert(mystring);                // copy insertion
s.insert(mystring+"dish");         // move insertion
s.insert(arr.begin(), arr.end());  // range insertion
s.insert( {"purple","orange"} );   // initializer list insertion
cout << "s contains:";
for (const string& x: s) cout << " " << x;
cout << '\n';
//s contains: green blue reddish white yellow black red orange purple

//=======
// ERASE
//=======
unordered_set<string> s =
{"USA","Canada","France","UK","Japan","Germany","Italy"};
s.erase( s.begin() );                // erasing by iterator
s.erase( "France" );                 // erasing by key
s.erase( s.find("Japan"), s.end() ); // erasing by range
cout << "s contains:";
for ( const string& x: s ) cout << " " << x;
cout << '\n'; // s contains: Canada USA Italy

//======
// FIND
//======
unordered_set<string> s{"red","green","blue"};
auto it = s.find("black");
assert (it == s.end());
assert (s.find("red") != s.end());

//=======
// COUNT
//=======
unordered_set<string> s { "hat", "umbrella", "suit" };
for (auto& x: {"hat","sunglasses","suit","t-shirt"}) {
    if (s.count(x) > 0) cout << "s has " << x << '\n';
    else cout << "s has no " << x << '\n';
} /* 
s has hat
s has no sunglasses
s has suit
s has no t-shirt */