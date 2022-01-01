#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef long double ld;

const ld PI = 3.14159265358979323;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct Frac {
	ll num, denum; Frac() {}
	Frac(ll _num, ll _denum) {
		ll g = gcd(abs(_num), abs(_denum));
		num = abs(_num) / g; denum = abs(_denum) / g;
		if ((_num < 0) ^ (_denum < 0)) { num = -num; }
	}
	Frac(ll x) : Frac(x, 1) {}
	Frac(const Frac& rhs) : num(rhs.num), denum(rhs.denum) {}

	Frac operator *(const Frac& rhs) const { return Frac(num * rhs.num, denum * rhs.denum); }
	Frac operator +(const Frac& rhs) const { return Frac(num * rhs.denum + denum * rhs.num, denum * rhs.denum); }
	Frac operator -(const Frac& rhs) const { return Frac(num * rhs.denum - denum * rhs.num, denum * rhs.denum); }
	Frac operator /(const Frac& rhs) const { return Frac(num * rhs.denum, denum * rhs.num); }

	Frac operator *=(const Frac& rhs) { return *this = *this * rhs; }
	Frac operator +=(const Frac& rhs) { return *this = *this + rhs; }
	Frac operator -=(const Frac& rhs) { return *this = *this - rhs; }
	Frac operator /=(const Frac& rhs) { return *this = *this / rhs; }
	Frac absolute() const { return Frac(abs(num), abs(denum)); }
	bool operator ==(const Frac& rhs) const { return num == rhs.num && denum == rhs.denum; }
	bool operator <(const Frac& rhs) const { return num * rhs.denum < denum* rhs.num; }
	bool operator >(const Frac& rhs) const { return num * rhs.denum > denum * rhs.num; }
	template<class T> T eval() { return (T)num / (T)denum; }
};

struct Point {
	Frac x, y; Point() {}
	Point(Frac _x, Frac _y) : x(_x), y(_y) {}
	Point(ll x1, ll y1, ll x2, ll y2) : x(Frac(x1, y1)), y(Frac(x2, y2)) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

	bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }
};

Frac dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
Frac crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }
Frac dist2(const Point& p1, const Point& p2) { //Returns the square of the distance
	Frac dx = p1.x - p2.x, dy = p1.y - p2.y;
	return (dx * dx) + (dy * dy);
}

struct Line {
	Point A, B; Line() {}
	Line(Point _a, Point _b) : A(_a), B(_b) {}

	Frac length2() const { return dist2(A, B); }
	Frac slope() const { return (A.y - B.y) / (A.x - B.x); }
	Frac yInt() const { return A.y - (slope() * A.x); }

	// Assumes points have positive integer coordinates
	// Returns number of lattice points on the line
	ll lattice() {
		ll x = abs(A.x.num - B.x.num);
		ll y = abs(A.y.num - B.y.num);
		return gcd(x, y) + 1;
	}

	Frac distToPoint2(const Point& p) {					// not tested
		Frac a = slope(), b(-1), c = yInt();
		Frac num = a * p.x + b * p.y + c; num *= num;
		Frac denum = a * a + b * b;			// + c*c?
		return num / denum;
	}

	// Assumes the lines are not parallel
	Point lineIntersect(const Line& rhs) {
		Frac a = slope(), c = rhs.slope();
		Frac b = yInt(), d = rhs.yInt();
		Frac x = (d - b) / (a - c);
		return Point(x, a * x + b);
	}

	// Calculate the angle between the 2 lines			not tested
	template<class T> T CalcAngle(const Line& rhs) {
		Point p1 = B - A, p2 = rhs.B - rhs.A;
		T a1 = atan2(p1.y.eval<T>(), p1.x.eval<T>());
		T a2 = atan2(p2.y.eval<T>(), p2.x.eval<T>());
		return abs(a2 - a1);
	}

	// Returns the projection of P onto this line		not tested
	Point proj(const Point& P) {
		Point D = B - A;
		Frac tmp = dotProduct(P - A, D) / dotProduct(D, D);
		D.x *= tmp; D.y *= tmp;
		return A + D;
	}
};

struct Circle {
	//Stores the square of the radius
	Point O; Frac R2; Circle() {}
	Circle(Point c, Frac r) : O(c), R2(r* r) {}
	Circle(Point p1, Point p2, Point p3) {
		Frac x12 = p1.x - p2.x, x13 = p1.x - p3.x, x31 = p3.x - p1.x, x21 = p2.x - p1.x;
		Frac y12 = p1.y - p2.y, y13 = p1.y - p3.y, y31 = p3.y - p1.y, y21 = p2.y - p1.y;
		Frac sx13 = p1.x * p1.x - p3.x * p3.x, sx21 = p2.x * p2.x - p1.x * p1.x;
		Frac sy13 = p1.y * p1.y - p3.y * p3.y, sy21 = p2.y * p2.y - p1.y * p1.y;

		Frac gN = sx13 * y12 + sy13 * y12 + sx21 * y13 + sy21 * y13;
		Frac gD = x31 * y12 - x21 * y13, g = Frac(-1, 2) * (gN / gD);
		Frac fN = sx13 * x12 + sy13 * x12 + sx21 * x13 + sy21 * x13;
		Frac fD = y31 * x12 - y21 * x13, f = Frac(-1, 2) * (fN / fD);

		O = Point(g, f); R2 = dist2(O, p1);
	}

	// Power of a point P wrt the circle = square length of tangent from P to the circle
	Frac power(const Point& p) const { return (p.x - O.x) * (p.x - O.x) + (p.y - O.y) * (p.y - O.y) - R2; }
};

struct Polygon {
	//assumes clockwise/counterclockwise order and first point appears on both ends
	int n;	// n = number of distinct points + 1
	vector<Point> points;
	Polygon(int _n) : n(_n) { points.resize(n); }

	Frac area() const { //Returns double the area
		Frac a = 0;
		for (int i = 0; i < n - 1; i++)
			a += crossProduct(points[i], points[i + 1]);
		return a.absolute() / 2;
	}

	ll boundaryLattice() const { //Assumes points have integer coordinates
		ll B = 0;
		for (int i = 0; i < n - 1; i++)
			B += Line(points[i], points[i + 1]).lattice() - 1;
		return B;
	}

	ll interiorLattice() const { //Pick theorem: A = I + B/2 - 1
		Frac A = area(); ll B = boundaryLattice();
		Frac res = A - Frac(B, 2) + 1;
		return res.eval<ll>();
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);


}