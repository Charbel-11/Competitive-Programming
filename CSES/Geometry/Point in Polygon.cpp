#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point(const Point& rhs) :x(rhs.x), y(rhs.y) {}

	bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

struct Polygon {
	//assumes clockwise/counterclockwise order and first point appears on both ends
	int n;	// n = number of distinct points + 1
	vector<Point> points;
	Polygon(int _n) : n(_n), points(_n) {}
	Point& operator [](const int i) { return points[i]; }
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m; cin >> n >> m;
	Polygon pol(n + 1);
	for (int i = 0; i < n; i++) { cin >> pol[i]; }
	pol[n] = pol[0];

	for (int i = 0; i < m; i++) {
		Point cur; cin >> cur;
		int state = pointInsidePolygon(pol, cur);
		if (state == 0) { cout << "OUTSIDE" << '\n'; }
		else if (state == 1) { cout << "INSIDE" << '\n'; }
		else { cout << "BOUNDARY" << '\n'; }
	}
}