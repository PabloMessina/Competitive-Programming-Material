// references:
//   http://www.cplusplus.com/reference/deque/deque/
//   https://www.geeksforgeeks.org/deque-cpp-stl/
// SUMMARY: deque can do the same things as vector
//  + push_front() + emplace_front()
//  - contiguous memory allocation is not guaranteed
//  (elements may be stored in fragmented chunks of memory)
deque<int> dq = { 1, 2, 3 };
dq.push_back(8); // { 1, 2, 3, 8 }
dq.push_front(100); // { 100, 1, 2, 3, 8 }
dq.pop_back(); // { 100, 1, 2, 3 }
dq.pop_front(); // { 1, 2, 3}