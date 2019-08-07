// references:
// http://www.cplusplus.com/reference/set/set/
// http://www.cplusplus.com/reference/set/multiset/
#define rep(i,a,b) for(int i=a; i<=b; i++)

//================
// INITIALIZATION
//================
// set
set<int> s{1, 2, 3, 4, 4, 5, 5, 5, 2, 2, 2};
for (int x : s) cout << x; // 12345
// multiset
multiset<int> ms{1, 2, 3, 4, 4, 5, 5, 5, 2, 2, 2};
for (int x : s) cout << x; // 12222344555

//========
// INSERT
//========
// set
set<int> s;
rep(i,1,5) s.insert(i*10);    // 10 20 30 40 50
auto ret = s.insert(20);  // no new element inserted
auto it = ret.first;
if (it.second) cout << "20 inserted for the first time\n";
else cout << "20 already in set\n";
int myints[]= {5,10,15};     // 10 already in set, not inserted
s.insert(myints,myints+3);
cout << "s contains:";
for (int x : s) cout << ' ' << x;
cout << '\n'; // 5 10 15 20 30 40 50
// multiset
// ** same as set, but allows duplicates, so insert returns an iterator
//    not a pair

//=======
// ERASE
//=======
// -- set
set<int> s;
rep(i,1,9) s.insert(i*10);  // 10 20 30 40 50 60 70 80 90
auto it = s.begin();
++it; // "it" points now to 20
s.erase(it); // erase by pointer
s.erase(40); // erase by value
it = s.find(60); // iterator pointing to 60
s.erase(it, s.end()); // erase everything in range [it, s.end())
// s = 10 30 50
// -- multiset
multiset<int> ms;
ms.insert (40);               // 40
rep(i,1,6) ms.insert(i*10);   // 10 20 30 40 40 50 60
auto it=ms.begin();
it++;                         //    ^
ms.erase(it);                // 10 30 40 40 50 60
ms.erase(40);                // 10 30 50 60
it=ms.find(50);
ms.erase(it, ms.end());      // 10 30

//=======
// FIND
//=======
// -- set
set<int> s;
rep(i,1,5) s.insert(i*10);  // 10 20 30 40 50
auto it=s.find(20);
s.erase(it);                // 10 30 40 50
s.erase(s.find(40));        // 10 30 50
// -- multiset
// ** same as set

//===============================
// lower_bound() & upper_bound()
//===============================
// -- set
set<int> s;
rep(i,1,9) s.insert(i*10);    // 10 20 30 40 50 60 70 80 90
auto itlow=s.lower_bound(30); //       ^
auto itup=s.upper_bound(60);  //                   ^
s.erase(itlow,itup);          // 10 20 70 80 90
// -- multiset
multiset<int> ms{30, 10, 10, 40, 30, 90}; // 10 10 30 30 40 90
auto itlow = ms.lower_bound(30);          //       ^
auto itup = ms.upper_bound(40);           //                ^
ms.erase(itlow,itup);                     // 10 20 90

//=======================
// multiset::equal_range
//=======================
int myints[] = {77,30,16,2,30,30};
multiset<int> ms(myints, myints+6);  // 2 16 30 30 30 77
auto ret = ms.equal_range(30);       //      ^        ^
// ret.first -> first 30 (same as ms.lower_bound(30))
// ret.second -> 77 (same as ms.upper_bound(30))
ms.erase(ret.first, ret.second);     // 2 16 77

//=======
// COUNT
//=======
// --- set
set<int> s{3, 6, 9, 12};
rep(i,0,9) {
    cout << i;
    if (s.count(i) > 0) cout << " is an element of s.\n";
    else cout << " is not an element of s.\n";
}
// --- multiset
multiset<int> ms{10,73,12,22,73,73,12};
cout << ms.count(73); // 3

//=============================
// SET/MULTISET of Custom Data
//=============================
struct CustomData {
    int x; string name;
    CustomData(int x, string n) : x(x), name(n) {}
    // define operator <
    bool operator<(const CustomData& rhs) const {
        return x < rhs.x;
    }
};
set<CustomData> s;
multiset<CustomData> ms;
s.emplace(1, "foo");
s.emplace(2, "bar");
ms.emplace(-12, "bla");