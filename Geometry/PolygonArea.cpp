//=============================================
// Area of 2D non self intersecting Polygon 
//=============================================
//based on Green Theorem
#include <cmath> //fabs
#include <cstdlib> //abs
struct Point {
	int x; int y;
};

int N = 1000;

Point points[N];

double A = 0;
for(int i = 0; i < N-1; ++i) {
	A += (points[i+1].x + points[i].x)*(points[i+1].y - points[i].y);
}
A += (points[0].x + points[N-1].x)*(points[0].y - points[N-1].y);
A /= 2;
//if float
A = fabs(A);
//if integer
A = abs(A);