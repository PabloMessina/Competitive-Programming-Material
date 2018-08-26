#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

struct Point { double x, y; };

// Computes the line integral of the vector field <0,x> over the arc of the circle with radius 'r'
// and x-coordinate 'x' from angle 'a' to angle 'b'. The 'y' goes away in the integral so it
// it doesn't matter.
// This can be done using a parameterization of the arc in polar coordinates:
// x(t) = x + r * cos(t)
// y(t) = y + r * sin(t)
// a <= t <= b
// The final integral can be seen here:
// https://www.wolframalpha.com/input/?i=integral((x+%2B+r*cos(t))+*+derivative(y+%2B+r*sin(t))+*+dt,+t%3Da..b)
double arc_integral(double x, double r, double a, double b) {
    return x * r * (sin(b) - sin(a)) + r * r * 0.5 * (0.5 * (sin(2*b) - sin(2*a)) + b - a);
}

// Computes the line integral of the vector field <0, x> over the directed segment a -> b
// This can be done using the parameterization:
// x(t) = a.x + (b.x - a.x) * t
// y(t) = a.y + (b.y - a.y) * t
// 0 <= t <= 1
double segment_integral(Point& a, Point& b) {
    return 0.5 * (a.x + b.x) * (b.y - a.y);
}