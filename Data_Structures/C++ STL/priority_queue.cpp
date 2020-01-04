// references:
// http://www.cplusplus.com/reference/queue/priority_queue/
// https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/

//====================
// 1) MAXHEAP of ints
//====================
priority_queue<int> q;
q.push(30);
q.push(100);
q.push(25);
q.push(40);
cout << "Popping out elements...";
while (!q.empty()) {
    cout << ' ' << q.top();
    q.pop();
}
cout << '\n';
// Popping out elements... 100 40 30 25

//====================
// 2) MINHEAP of ints
//====================
priority_queue<int, vector<int>, greater<int>> q;
q.push(30);
q.push(100);
q.push(25);
q.push(40);
cout << "Popping out elements...";
while (!q.empty()) {
    cout << ' ' << q.top();
    q.pop();
}
cout << '\n';
// Popping out elements... 25 30 40 100

//====================================
// 3) custom data + custom comparator
//====================================

// option 1: overload operator< inside your struct/class
struct Event {
    double time; string name;
    Event (double t, string n) : time(t), name(n) {}
    bool overload<(const Event& rhs) const {
        // define your < operator however you want
        return time > rhs.time;
    }
};
priority_queue<Event> q;

// option 2: use a functor
struct Event {
    double time; string name;
    Event (double t, string n) : time(t), name(n) {}
};
struct EventCmp {
    bool operator()(const Event& lhs, const Event& rhs) {
        return lhs.time > rhs.time;
    }
};
priority_queue<Event, vector<Event>, EventCmp> q;

// option 3: use a lambda function
struct Event {
    double time; string name;
    Event (double t, string n) : time(t), name(n) {}
};
auto cmp = [](const Event& lhs const Event& rhs) {
    return lhs.time > rhs.time;
};
priority_queue<Event, vector<Event>, decltype(cmp)> q(cmp);

// usage example
q.emplace(10.2, "Peter");
q.emplace(2.7, "Mary");
q.emplace(5.3, "John");
q.emplace(0.3, "Bob");
cout << "Events:";
while (!q.empty()) {
    Event& e = q.top();
    cout << " (" << e.time << ',' << e.name << ")";
    q.pop();
}
// Events: (0.3,Bob) (2.7,Mary) (5.3,John) (10.2,Peter)