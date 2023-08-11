#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const double eps = 1e-12;
const double pi = 3.14159265358979323846;

struct Point {
	double x, y; Point() {}
	Point(double _x, double _y) : x(_x), y(_y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

	Point operator * (double c) const { return Point(x * c, y * c); }
	Point operator / (double c) const { return Point(x / c, y / c); }
};

double dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
double dist(const Point& p1, const Point& p2) {
	double dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrt((dx * dx) + (dy * dy));
}

struct Circle {
	Point O; double R; Circle() {}
	Circle(Point c, double r) : O(c), R(r) {}
	Circle(Point p1, Point p2, Point p3) {		//not tested
		double x12 = p1.x - p2.x, x13 = p1.x - p3.x, x31 = p3.x - p1.x, x21 = p2.x - p1.x;
		double y12 = p1.y - p2.y, y13 = p1.y - p3.y, y31 = p3.y - p1.y, y21 = p2.y - p1.y;
		double sx13 = p1.x * p1.x - p3.x * p3.x, sx21 = p2.x * p2.x - p1.x * p1.x;
		double sy13 = p1.y * p1.y - p3.y * p3.y, sy21 = p2.y * p2.y - p1.y * p1.y;

		double gN = sx13 * y12 + sy13 * y12 + sx21 * y13 + sy21 * y13;
		double gD = x31 * y12 - x21 * y13, g = (-1 / 2.0) * (gN / gD);
		double fN = sx13 * x12 + sy13 * x12 + sx21 * x13 + sy21 * x13;
		double fD = y31 * x12 - y21 * x13, f = (-1 / 2.0) * (fN / fD);

		O = Point(g, f); R = dist(O, p1);
	}

	// Power of a point P wrt the circle = square length of tangent from P to the circle
	double power(const Point& p) const { return (p.x - O.x) * (p.x - O.x) + (p.y - O.y) * (p.y - O.y) - R * R; }
};

// Find the points where the two circles intersect; assumes they intersect at 1 or 2 points
vector<Point> FindCircleCircleIntersections(const Circle& c0, const Circle& c1){	//not tested
	double d = dist(c0.O, c1.O);	

	double a = (c0.R * c0.R - c1.R * c1.R + d * d) / (2 * d);
	double h = sqrt(c0.R * c0.R - a * a);

	double cx2 = c0.O.x + a * (c1.O.x - c0.O.x) / d;
	double cy2 = c0.O.y + a * (c1.O.y - c0.O.y) / d;

	Point P1 = Point((cx2 + h * (c1.O.y - c0.O.y) / d), (cy2 - h * (c1.O.x - c0.O.x) / d));
	Point P2 = Point((cx2 - h * (c1.O.y - c0.O.y) / d), (cy2 + h * (c1.O.x - c0.O.x) / d));
	return { P1, P2 };
}

// Find the tangent points for the circle c and an external point p
vector<Point> FindTangents(Circle& C, const Point &p) {			//not tested
	double L = sqrt(C.power(p));
	return FindCircleCircleIntersections(C, Circle(p, L));
}

// Compute intersection of the line (AB) with the circle C
vector<Point> CircleLineIntersection(Point a, Point b, const Circle& c) {	//not tested
	b = b - a; a = a - c.O;	
	double A = dotProduct(b, b), B = dotProduct(a, b), C = dotProduct(a, a) - c.R * c.R;
	double D = B * B - A * C;
	if (D < -eps) { return {}; }

	vector<Point> ans = { c.O + a + b * (-B + sqrt(D + eps)) / A };
	if (D > eps) { ans.push_back(c.O + a + b * (-B - sqrt(D)) / A); }

	return ans;
}