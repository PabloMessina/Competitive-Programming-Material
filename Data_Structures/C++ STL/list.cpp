// full documentation:
// http://www.cplusplus.com/reference/list/list/
// https://www.geeksforgeeks.org/list-cpp-stl/

//========
// INSERT
//========
// http://www.cplusplus.com/reference/list/list/insert/

list<int> mylist;
list<int>::iterator it;
// set some initial values:
rep(i,1,5) mylist.push_back(i);               // 1 2 3 4 5
it = mylist.begin();
++it;       // it points now to number 2           ^
mylist.insert(it,10);                         // 1 10 2 3 4 5
// "it" still points to number 2                      ^
mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
--it;       // it points now to the second 20            ^
vector<int> myvector (2,30);
mylist.insert (it,myvector.begin(),myvector.end());
                                            // 1 10 20 30 30 20 2 3 4 5
                                            //               ^
cout << "mylist contains:";
for (int x : mylist) cout << ' ' << x;
cout << '\n';
// mylist contains: 1 10 20 30 30 20 2 3 4 5

//=======
// ERASE
//=======
// http://www.cplusplus.com/reference/list/list/erase/

list<int> mylist;
list<int>::iterator it1,it2;
// set some values:
rep(i,1,9) mylist.push_back(i*10);
                            // 10 20 30 40 50 60 70 80 90
it1 = it2 = mylist.begin(); // ^^
advance (it2,6);            // ^                 ^
++it1;                      //    ^              ^

it1 = mylist.erase(it1);    // 10 30 40 50 60 70 80 90
                            //    ^           ^

it2 = mylist.erase(it2);    // 10 30 40 50 60 80 90
                            //    ^           ^
++it1;                      //       ^        ^
--it2;                      //       ^     ^
mylist.erase(it1,it2);      // 10 30 60 80 90
                            //        ^
cout << "mylist contains:";
for (int x : mylist) cout << ' ' << x;
cout << '\n';
// mylist contains: 10 30 60 80 90
