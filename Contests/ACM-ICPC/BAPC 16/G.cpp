#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef long double ld;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct Frac {
	ll num, denum; Frac() {}
	Frac(ll _num, ll _denum) {
		ll g = gcd(abs(_num), abs(_denum));
		num = abs(_num) / g; denum = abs(_denum) / g;
		if ((_num < 0) ^ (_denum < 0)) { num = -num; }
	}
	Frac(ll x) : Frac(x, 1) {}
	Frac operator *(const Frac &rhs) { return Frac(num * rhs.num, denum * rhs.denum); }
	Frac operator +(const Frac &rhs) { return Frac(num * rhs.denum + denum * rhs.num, denum * rhs.denum); }
	Frac operator -(const Frac &rhs) { return Frac(num * rhs.denum - denum * rhs.num, denum * rhs.denum); }
	Frac operator /(const Frac &rhs) { return Frac(num * rhs.denum, denum * rhs.num); }
	Frac operator *=(const Frac &rhs) { return *this = *this * rhs; }
	Frac operator +=(const Frac &rhs) { return *this = *this + rhs; }
	Frac operator -=(const Frac &rhs) { return *this = *this - rhs; }
	Frac operator /=(const Frac &rhs) { return *this = *this / rhs; }
	Frac absolute() { return Frac(abs(num), abs(denum)); }
	bool operator ==(const Frac &rhs) const { return num == rhs.num && denum == rhs.denum; }
	bool operator <(const Frac &rhs) const { return num * rhs.denum < denum * rhs.num; }
	bool operator >(const Frac &rhs) const { return num * rhs.denum > denum * rhs.num; }
	template<class T> T eval() { return (T)num / (T)denum; }
};

struct Point {
	Frac x, y; Point() {}
	Point(Frac _x, Frac _y) : x(_x), y(_y) {}
	Point(ll x1, ll y1, ll x2, ll y2) : x(Frac(x1, y1)), y(Frac(x2, y2)) {}
};

Frac dist2(Point p1, Point p2) { //Returns the square of the distance
	Frac dx = p1.x - p2.x, dy = p1.y - p2.y;
	return (dx * dx) + (dy * dy);
}

struct Line {
	Point A, B; Line() {}
	Line(Point _a, Point _b) : A(_a), B(_b) {}

	Frac length2() { return dist2(A, B); } //returns the square
	Frac slope() { return (A.y - B.y) / (A.x - B.x); }
	Frac yInt() { return A.y - (slope() * A.x); }

	Point lineIntersect(Line rhs) {
		Frac a = slope(), c = rhs.slope();
		if (a == c) { return Point(0.5, 0.5); }
		Frac b = yInt(), d = rhs.yInt();
		Frac x = (d - b) / (a - c);
		return Point(x, a*x + b);
	}
};

struct b {
	int x, y, d;

	b(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {}

	bool operator<(b& rhs) {
		return d < rhs.d;
	}
};

int dist(pair<int, int> &p, b &beacon) {
	return abs(p.first - beacon.x) + abs(p.second - beacon.y);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N; cin >> N;
	if (N == 1) { 
		int x, y, d; cin >> x >> y >> d;
		if (d == 0) { cout << x << " " << y << endl; }
		else { cout << "uncertain" << endl; }
		return 0; 
	}

	vector<b> beacons;
	for (int i = 0; i < N; i++) {
		int x, y, d; cin >> x >> y >> d;
		beacons.push_back(b(x, y, d));
	}

	sort(beacons.begin(), beacons.end());

	vector<pair<int, int>> candidates;
	int curX, curY;
	int dx[] = { -1,1 };
	int dy[] = { -1,1 };

	for (int dd : dx) {
		for (int yy : dy) {
			curX = beacons[0].x; curY = beacons[0].y + yy * beacons[0].d;
			pair<int, int> p = { curX,curY };
			if (dist(p, beacons[1]) == beacons[1].d) { candidates.push_back({ curX, curY }); }
			for (int rem = 0; rem < beacons[0].d; rem++) {
				curX += dd; curY += (-yy); p = { curX,curY };
				if (dist(p, beacons[1]) == beacons[1].d) { candidates.push_back({ curX, curY }); }
			}
		}
	}

	for (int i = 2; i < N; i++) {
		vector<pair<int, int>> newCand;
		for (auto &p : candidates) {
			if (dist(p, beacons[i]) == beacons[i].d) { newCand.push_back(p); }
		}
		candidates = newCand;
	}

	if (candidates.size() == 0) { cout << "impossible" << endl; }
	else if (candidates.size() == 1) { cout << candidates[0].first << " " << candidates[0].second << endl; }
	else { cout << "uncertain" << endl; }
}