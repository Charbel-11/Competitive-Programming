#include <iostream>
#include <vector>
#include <algorithm>
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

ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

struct Polygon {
	//assumes clockwise/counterclockwise order and first point appears on both ends
	int n;	// n = number of distinct points + 1
	vector<Point> points;
	Polygon(int _n) : n(_n), points(_n) {}
	Point& operator [](const int i) { return points[i]; }

	ll area() { //Returns double the area
		ll a = 0;
		for (int i = 0; i < n - 1; i++)
			a += crossProduct(points[i], points[i + 1]);
		return abs(a);
	}

	ll boundaryLatticeCount() { //Assumes points have integer coordinates
		ll B = 0;
		for (int i = 0; i < n - 1; i++) {
			ll dx = abs(points[i].x - points[i + 1].x);
			ll dy = abs(points[i].y - points[i + 1].y);
			B += gcd(dx, dy);
		}
		return B;
	}

	//Pick's theorem: A = I + B/2 - 1
	ll interiorLatticeCount() {
		ll A = area(), B = boundaryLatticeCount();
		return (A - B + 2) >> 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n;
	Polygon p(n + 1);
	for (int i = 0; i < n; i++) { cin >> p[i]; }
	p[n] = p[0];

	cout << p.interiorLatticeCount() << " " << p.boundaryLatticeCount() << '\n';
}