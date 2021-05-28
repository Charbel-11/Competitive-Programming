#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;
const double pi = 3.14159265358979323846;

struct Point {
	double x, y; Point() {}
	Point(double _x, double _y) : x(_x), y(_y) {}
};

// Calculate the angle between the line from p1 to p2
// and the line from p3 to p4
double CalcAngle(Point &p1, Point &p2, Point &p3, Point &p4) {
	double x1 = p2.x - p1.x, y1 = p2.y - p1.y;
	double x2 = p4.x - p3.x, y2 = p4.y - p3.y;
	double a1 = atan2(y1, x1), a2 = atan2(y2, x2);
	return abs(a2 - a1);
}

double dist(Point p1, Point p2) {
	double dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrt(dx * dx + dy * dy);
}

// Returns whether line ab and line cd intersect (i.e. are not parallel)
// In which case the intersection point is (x,y)
bool intersection(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd, double& x, double& y){
	int d = (xa - xb)*(yc - yd) - (xc - xd)*(ya - yb);	
	if (d == 0) { return false; }	//same slope
	x = -((ll)(xa - xb)*(xc*yd - xd * yc) - (ll)(xc - xd)*(xa*yb - xb * ya)) / (double)(d);
	y = ((ll)(ya - yb)*(yc*xd - yd * xc) - (ll)(yc - yd)*(ya*xb - yb * xa)) / (double)(d);
	return true;
}

// Returns whether (x,y) is (strictly) to the left of the (extended) line from (x1,y1) to (x2,y2)
bool totheleft(int x, int y, int x1, int y1, int x2, int y2){
	return (x - x1)*(y - y2) > (x - x2)*(y - y1);
}

//Line is (x1,y1)->(x2,y2), Point is (x0,y0)
double lineToPtDist(ll x1, ll y1, ll x2, ll y2, ll x0, ll y0) {
	ll res = abs((y2 - y1)*x0 - (x2 - x1)*y0 + x2 * y1 - y2 * x1);
	ll dy = y2 - y1;
	ll dx = x2 - x1;
	double den = sqrt(dy*dy + dx * dx);

	return (double)res / den;
}

double dot(ll xa, ll ya, ll xb, ll yb) { return xa * xb + ya * yb; }
double dotSelf(ll xa, ll ya) { return xa * xa + ya * ya; }

//Projection of point A onto line BC
pair<double, double> proj(ll xa, ll ya, ll xb, ll yb, ll xc, ll yc) { 
	pair<double, double> d = { xc - xb, yc - yb };
	pair<double, double> ans = { xb, yb };

	double tmp = dot(xa - xb, ya - yb, d.first, d.second) / dotSelf(d.first, d.second);
	d.first *= tmp; d.second *= tmp;
	ans.first += d.first; ans.second += d.second;
	return ans;
}



typedef complex<double> point;
#define x real()
#define y imag()
#define PI 3.1415926535897932384626

//Function for Rotation of P about Q by angle theta (in radians)
point rotate(point P, point Q, double theta) {
	return (P - Q) * polar(1.0, theta) + Q;
}