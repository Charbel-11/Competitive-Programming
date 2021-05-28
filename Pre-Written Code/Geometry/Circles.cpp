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

// Find the points where the two circles intersect; assumes they intersect at 1 or 2 points
vector<Point> FindCircleCircleIntersections(Point c0, double r0, Point c1, double r1){
	// Find the distance between the centers.
	double dx = c0.x - c1.x, dy = c0.y - c1.y;
	double d = sqrt(dx * dx + dy * dy);

	double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
	double h = sqrt(r0 * r0 - a * a);

	// Find P2.
	double cx2 = c0.x + a * (c1.x - c0.x) / d;
	double cy2 = c0.y + a * (c1.y - c0.y) / d;

	// Get the points P3.
	Point P1 = Point((cx2 + h * (c1.y - c0.y) / d), (cy2 - h * (c1.x - c0.x) / d));
	Point P2 = Point((cx2 - h * (c1.y - c0.y) / d), (cy2 + h * (c1.x - c0.x) / d));
	return { P1, P2 };
}

// Find the tangent points for this circle and external point
vector<Point> FindTangents(Point &C, double r, Point &P) {
	Point pt1, pt2;
	// Find the distance squared from the external point to the circle's center.
	double dx = C.x - P.x, dy = C.y - P.y;
	double D_squared = dx * dx + dy * dy;

	// Find the distance from the external point to the tangent points.
	double L = sqrt(D_squared - r * r);
	return FindCircleCircleIntersections(C, r, P, L);
}



struct Point {
	Frac x, y; Point() {}
	Point(Frac _x, Frac _y) : x(_x), y(_y) {}
	Point(ll _x, ll _y) : x(Frac(_x)), y(Frac(_y)) {}
};

Frac dist2(Point p1, const Point p2) {
	Frac dx = p1.x - p2.x, dy = p1.y - p2.y;
	return (dx * dx) + (dy * dy);
}

//Find the center of a circle given 3 points that defines it
//Center has coordinates (Frac g, Frac f)
Point findCircle(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	ll x12 = x1 - x2, x13 = x1 - x3, x31 = x3 - x1, x21 = x2 - x1;
	ll y12 = y1 - y2, y13 = y1 - y3, y31 = y3 - y1, y21 = y2 - y1;

	ll sx13 = x1 * x1 - x3 * x3, sx21 = x2 * x2 - x1 * x1;
	ll sy13 = y1 * y1 - y3 * y3, sy21 = y2 * y2 - y1 * y1;

	Frac f(-((sx13) * (x12)+(sy13) * (x12)+(sx21) * (x13)+(sy21) * (x13)), (2 * ((y31) * (x12)-(y21) * (x13))));
	Frac g(-((sx13) * (y12)+(sy13) * (y12)+(sx21) * (y13)+(sy21) * (y13)), (2 * ((x31) * (y12)-(x21) * (y13))));

	return Point(g, f);
}


//CIRCLE INTERSECTION WITH LINE/CIRCLE

typedef long double ld;
ld EPS = 1e-12;

struct PT {
	ld x, y; PT() {}
	PT(ld x, ld y) : x(x), y(y) {}
	PT(const PT &p) : x(p.x), y(p.y) {}
	PT operator + (const PT &p) const { return PT(x + p.x, y + p.y); }
	PT operator - (const PT &p) const { return PT(x - p.x, y - p.y); }
	PT operator * (ld c) const { return PT(x*c, y*c); }
	PT operator / (ld c) const { return PT(x / c, y / c); }
};
ld dot(PT p, PT q) { return p.x*q.x + p.y*q.y; }
ld dist2(PT p, PT q) { return dot(p - q, p - q); }

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p) { return PT(-p.y, p.x); }

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<PT> CircleLineIntersection(PT a, PT b, PT c, ld r) {
	vector<PT> ret;
	b = b - a; a = a - c;	
	ld A = dot(b, b), B = dot(a, b), C = dot(a, a) - r * r;
	ld D = B * B - A * C;
	if (D < -EPS) { return ret; }
	ret.push_back(c + a + b * (-B + sqrt(D + EPS)) / A);
	if (D > EPS) { ret.push_back(c + a + b * (-B - sqrt(D)) / A); }
	return ret;
}
// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleIntersection(PT a, PT b, ld r, ld R) {
	vector<PT> ret;
	ld d = sqrt(dist2(a, b));
	if (d > r + R || d + min(r, R) < max(r, R)) return ret;
	ld x = (d*d - R * R + r * r) / (2 * d);
	ld y = sqrt(r*r - x * x);
	PT v = (b - a) / d;
	ret.push_back(a + v * x + RotateCCW90(v)*y);
	if (y > 0) { ret.push_back(a + v * x - RotateCCW90(v) * y); }
	return ret;
}



//MIN ENCLOSING CIRCLE

struct Point { ld X, Y; };
struct Circle { Point C; ld R2; };

ld dist2(const Point& a, const Point& b) {
	ld dx = a.X - b.X, dy = a.Y - b.Y;
	return (dx * dx + dy * dy);
}

bool isInsideCircle(const Circle& c, const Point& p) {
	return dist2(c.C, p) <= c.R2;
}

Point getCircleCenter(ld bx, ld by, ld cx, ld cy) {
	ld B = bx * bx + by * by;
	ld C = cx * cx + cy * cy;
	ld D = bx * cy - by * cx;
	return { (cy * B - by * C) / (2 * D),
			 (bx * C - cx * B) / (2 * D) };
}

Circle circleFrom3Points(const Point& A, const Point& B, const Point& C) {
	Point I = getCircleCenter(B.X - A.X, B.Y - A.Y, C.X - A.X, C.Y - A.Y);
	I.X += A.X; I.Y += A.Y; return { I, dist2(I, A) };
}

Circle smallestCircleFrom2Points(const Point& A, const Point& B) {
	Point C = { (A.X + B.X) / 2.0, (A.Y + B.Y) / 2.0 };
	return { C, dist2(A, B) / 4.0 };
}

bool isValidCircle(const Circle& c, const vector<Point>& P) {
	for (const Point& p : P)
		if (!isInsideCircle(c, p))
			return false;
	return true;
}

Circle minEnclosingCircleTrivial(vector<Point>& P) {
	assert(P.size() <= 3);
	if (P.empty()) { return { { 0, 0 }, 0 }; }
	else if (P.size() == 1) { return { P[0], 0 }; }
	else if (P.size() == 2) { return smallestCircleFrom2Points(P[0], P[1]); }

	for (int i = 0; i < 3; i++)
		for (int j = i + 1; j < 3; j++) {
			Circle c = smallestCircleFrom2Points(P[i], P[j]);
			if (isValidCircle(c, P)) return c;
		}

	return circleFrom3Points(P[0], P[1], P[2]);
}

// Returns the MEC using Welzl's algorithm 
// Takes a set of input points P and a set R points on the circle boundary. 
// n represents the number of points in P that are not yet processed. 
Circle welzlHelper(vector<Point>& P, vector<Point> R, int n) {
	// Base case when all points processed or |R| = 3 
	if (n == 0 || R.size() == 3) { return minEnclosingCircleTrivial(R); }

	// Pick a random point randomly 
	int idx = rand() % n; Point p = P[idx];
	swap(P[idx], P[n - 1]);

	// Get the MEC circle d from the 
	// set of points P - {p} 
	Circle d = welzlHelper(P, R, n - 1);

	// If d contains p, return d 
	if (isInsideCircle(d, p)) { return d; }

	// Otherwise, must be on the boundary of the MEC 
	R.push_back(p);

	// Return the MEC for P - {p} and R U {p} 
	return welzlHelper(P, R, n - 1);
}

Circle minEnclosingCircle(vector<Point>& P) {
	random_shuffle(P.begin(), P.end());
	return welzlHelper(P, {}, (int)P.size());
}