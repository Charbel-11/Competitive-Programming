#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}

	bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }

	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

//0: Colinear; 1: Clockwise (C is to the right of (AB)); 2: Counterclockwise (C is to the left of (AB))
int orientation(const Point& A, const Point& B, const Point& C) {
	ll x = crossProduct(C - A, B - A);
	return x ? 1 + (x < 0) : 0;
}

// Checks whether P is in the segment [AB]
bool pointInsideSegment(const Point& A, const Point& B, const Point& P) {
	if (P == A || P == B) { return true; }
	return crossProduct(A - P, B - P) == 0 && dotProduct(A - P, B - P) < 0;
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t; cin >> t;
	while (t--) {
		Point p1, p2, p3, p4;
		cin >> p1 >> p2 >> p3 >> p4;
		cout << (intersectionSegmentSegment(p1, p2, p3, p4) ? "YES" : "NO") << '\n';
	}
}