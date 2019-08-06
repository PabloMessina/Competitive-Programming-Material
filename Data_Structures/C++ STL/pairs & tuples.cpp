// references:
// https://www.geeksforgeeks.org/returning-multiple-values-from-a-function-using-tuple-and-pair-in-c/
// http://www.cplusplus.com/reference/utility/pair/
// http://www.cplusplus.com/reference/tuple/

// -----
// PAIR
// -----
// Example: pair of ints
typedef pair<int,int> ii; // use ii as abbreviation
// initialization
ii p(5,5); // option 1
ii p = make_pair(5,5) // option 2
ii p = {5, 5}; // option 3
// getting values
int x = p.first, y = p.second;
// modifying values
p.first++, p.second--; // p = {6, 4}

// ------
// TUPLES
// ------
// Example: tuples of 3 ints
typedef tuple<int,int,int> iii; // use iii as abbreviation
// initialization
iii t(5,5,5); // option 1
iii t = make_tuple(5,5,5); // option 2
iii t = {5, 5, 5}; // option 3
// getting values
int x,y,z;
x = get<0>(t), y = get<1>(t), z = get<2>(t); // option 1
tie(x,y,z) = t; // option 2
// modifying values
get<0>(t)++, get<1>(t)--, get<2>(t)+=2; // t = {6, 4, 7}