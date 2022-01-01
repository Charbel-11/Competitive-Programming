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

ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

struct Polygon {
	//assumes clockwise/counterclockwise order and first point appears on both ends
	vector<Point> points; int n;
	Polygon(int _n) : n(_n), points(_n) {}
	Point& operator [](const int i) { return points[i]; }

	ll area() { //Returns double the area
		ll a = 0;
		for (int i = 0; i < n - 1; i++)
			a += crossProduct(points[i], points[i + 1]);
		return abs(a);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n; 
	Polygon pol(n + 1);
	for (int i = 0; i < n; i++) { cin >> pol[i]; }
	pol.points.back() = pol[0];

	cout << pol.area() << '\n';
}