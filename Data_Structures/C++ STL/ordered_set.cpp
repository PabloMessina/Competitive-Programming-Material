// references:
// https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/
// https://www.geeksforgeeks.org/policy-based-data-structures-g/
// https://codeforces.com/blog/entry/11080
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
  
typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update
> ordered_set;
  
int main() { 
    ordered_set o_set;
    o_set.insert(5); 
    o_set.insert(1); 
    o_set.insert(2);   
    // Finding the second smallest element 
    // in the set using * because 
    //  find_by_order returns an iterator 
    cout << *(o_set.find_by_order(1)) << '\n';
    // Finding the number of elements 
    // strictly less than k=4 
    cout << o_set.order_of_key(4) << '\n';  
    // Finding the count of elements less  
    // than or equal to 4 i.e. striclty less 
    // than 5 if integers are present 
    cout << o_set.order_of_key(5) << '\n';  
    // Deleting 2 from the set if it exists 
    if (o_set.find(2) != o_set.end()) 
        o_set.erase(o_set.find(2));  
    // Now after deleting 2 from the set 
    // Finding the second smallest element in the set 
    cout << *(o_set.find_by_order(1)) << '\n';  
    // Finding the number of 
    // elements strictly less than k=4 
    cout << o_set.order_of_key(4) << '\n';
    return 0; 
}