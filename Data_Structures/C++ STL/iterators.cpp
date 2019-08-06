#define rep(i,a,b) for(int i=a; i<=b; i++)

// ------------
// std::next()
// ------------
// reference: http://www.cplusplus.com/reference/iterator/next/
list<int> mylist;
rep(i,1,10) mylist.push_back(i); // {1, 2, 3, ..., 10}
auto it = mylist.begin();
cout << *it << '\n'; // 1
cout << *next(it) << '\n'; // 2
cout << *next(it, 9) << '\n'; // 10

// ------------
// std::prev()
// ------------
// reference: http://www.cplusplus.com/reference/iterator/prev/
list<int> mylist;
rep(i,0,9) mylist.push_back(i*10);
cout << "The last element is " << *prev(mylist.end()) << '\n';
cout << "The second last element is " << *prev(mylist.end(), 2) << '\n';
// output:
// The last element is 90
// The second last element is 80

// --------------
// std::advance()
// --------------
// reference: http://www.cplusplus.com/reference/iterator/advance/
list<int> mylist;
rep(i,0,9) mylist.push_back(i*10);
auto it = mylist.begin();
advance (it,5);
cout << "The sixth element in mylist is: " << *it << '\n';

// ** std::next vs std::advance
// https://www.geeksforgeeks.org/stdnext-vs-stdadvance-in-cpp/

// --------------------------------------
// iterating over a list (with iterators)
// -------------------------------------
list<int> mylist = { 1, 2, 3, 4, 5};
// forward
for (auto it = mylist.begin(); it != mylist.end(); ++it) {
    cout << *it << '\n';
}
// backward
for (auto it = mylist.rbegin(); it != mylist.rend(); ++it) {
    cout << *it << '\n';
}

// ----------------------------------
// forward iteration (short syntax)
// ----------------------------------
for (int x : mylist) cout << x << '\n';