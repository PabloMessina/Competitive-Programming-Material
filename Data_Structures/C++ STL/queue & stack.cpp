// references:
// http://www.cplusplus.com/reference/queue/queue/
// https://www.geeksforgeeks.org/queue-cpp-stl/
// http://www.cplusplus.com/reference/stack/stack/
// https://www.geeksforgeeks.org/stack-in-cpp-stl/

//===== QUEUE =====
queue<int> q;
// adding to queue
rep(i,1,5) q.push(i); // q = {1, 2, 3, 4, 5}
// OR
rep(i,1,5) q.emplace(i); // q = {1, 2, 3, 4, 5}
// removing from queue
while (!q.empty()) {
    cout << q.front() << ' ';
    q.pop();
} // output: 1 2 3 4 5

//===== STACK =====
stack<int> s;
// adding to stack
rep(i,1,5) s.push(i); // s = {1, 2, 3, 4, 5}
// OR
rep(i,1,5) s.emplace(i); // s = {1, 2, 3, 4, 5}
// removing from stack
while (!s.empty()) {
    cout << s.top() << ' ';
    s.pop();
} // output: 5 4 3 2 1