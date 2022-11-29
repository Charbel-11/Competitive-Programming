#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

	bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }
ll dist2(const Point& A, const Point& B) { return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y); }

struct Polygon {
	//assumes clockwise/counterclockwise order and first point appears on both ends
	int n;	// n = number of distinct points + 1
	vector<Point> points;
	Polygon(int _n) : n(_n), points(_n) {}
	Point& operator [](const int i) { return points[i]; }

	ll area() const { //Returns double the area
		ll a = 0;
		for (int i = 0; i < n - 1; i++)
			a += crossProduct(points[i], points[i + 1]);
		return abs(a);
	}

	ll boundaryLatticeCount() const { //Assumes points have integer coordinates
		ll B = 0; 
		for (int i = 0; i < n - 1; i++) {
			ll dx = abs(points[i].x - points[i + 1].x);
			ll dy = abs(points[i].y - points[i + 1].y);
			B += gcd(dx, dy);
		}
		return B;
	}

	//Pick's theorem: A = I + B/2 - 1
	ll interiorLatticeCount() const { 
		ll A = area(), B = boundaryLatticeCount();
		return (A - B + 2) >> 1;
	}
};

//0: Colinear; 1: Clockwise (C is to the right of (AB)); 2: Counterclockwise (C is to the left of (AB))
int orientation(const Point& A, const Point& B, const Point& C) {
	ll x = crossProduct(C - B, B - A);
	return x ? 1 + (x < 0) : 0;
}

// Checks whether P is in the segment [AB]
bool pointInsideSegment(const Point& A, const Point& B, const Point& P) {
	if (P == A || P == B) { return true; }
	return crossProduct(A - P, B - P) == 0 && dotProduct(A - P, B - P) < 0;
}

// Checks whether P is in the triangle ABC
bool pointInTriangle(const Point& A, const Point& B, const Point& C, const Point& P) {
	ll ABC = abs(crossProduct(B - A, C - A));
	ll PAB = abs(crossProduct(A - P, B - P));
	ll PAC = abs(crossProduct(A - P, C - P));
	ll PBC = abs(crossProduct(B - P, C - P));
	return ABC == PAB + PAC + PBC;
}

// Checks whether segments [A1 B1] and [A2 B2] intersect
bool intersectionSegmentSegment(const Point& A1, const Point& B1, const Point& A2, const Point& B2) {
	int O1 = orientation(A1, B1, A2), O2 = orientation(A1, B1, B2);
	int O3 = orientation(A2, B2, A1), O4 = orientation(A2, B2, B1);
	if (O1 != O2 && O3 != O4) { return true; }

	if (O1 || O2) { return false; }
	if (pointInsideSegment(A1, B1, A2)) { return true; }
	if (pointInsideSegment(A1, B1, B2)) { return true; }
	if (pointInsideSegment(A2, B2, A1)) { return true; }
	return false;
}

// Finds the location of A w.r.t. P in O(n) time
// 0: Outside  1: Inside  2: Boundary
int pointInsidePolygon(Polygon& P, const Point& X) {
	bool boundary = false; int n = P.n - 1;
	for (int i = 0; i < n; i++) {
		if (pointInsideSegment(P[i], P[i + 1], X)) {
			boundary = true; break;
		}
	}
	if (boundary) { return 2; }

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		Point A = P[i], B = P[i + 1];
		if (A.x > B.x) { swap(A, B); }
		cnt += A.x <= X.x && B.x > X.x && orientation(X, A, B) == 1;
	}
	return cnt & 1;
}

// Checks if A is in a convex polygon P in O(logn) time				not tested
// First Points must be sorted by angle w.r.t. the first point
bool pointInConvexPolygon(const vector<Point>& P, const Point& X) {
	if (pointInsideSegment(P.front(), P.back(), X)) { return true; }
	if (orientation(P.front(), P.back(), X) == 2) { return false; }

	int l = 0, r = (int)P.size() - 1;
	while (l != r) {
		int mid = (l + r + 1) >> 1;
		bool b = orientation(P[0], P[mid], X) == 2;
		b ? l = mid : r = mid - 1;
	}
	return pointInTriangle(P.front(), P[l], P[l + 1], X);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);


}