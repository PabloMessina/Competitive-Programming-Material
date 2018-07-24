/* ======================================== */
/* Area of 2D non self intersecting Polygon */
/* ======================================== */
//based on Green's Theorem:
//http://math.blogoverflow.com/2014/06/04/greens-theorem-and-area-of-polygons/

#include <bits/stdc++.h>
int N = 1000;
struct Point { int x, y; };
Point P[N];

double area() {
    int A = 0;
    for (int i = N-1, j = 0; j < N; i=j++)
        A += (P[i].x + P[j].x) * (P[j].y - P[i].y);
    return fabs(A * 0.5);
}