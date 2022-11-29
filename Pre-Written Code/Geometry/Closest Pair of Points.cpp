#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll dist2(Point A, Point B) { return (A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y); }

bool yCoord(const Point& lhs, const Point& rhs) { return lhs.y < rhs.y; }
bool xCoord(const Point& lhs, const Point& rhs) { return lhs.x < rhs.x; }

// Returns the square of the minimum distance between any two points in P in O(nlogn) 
ll closestPair2(vector<Point>& P) {
	if (P.size() < 2) { return (ll)8e18; }

	int n = (int)P.size(), mid = n >> 1; ll Xmid = P[mid].x;
	vector<Point> L(P.begin(), P.begin() + mid);
	vector<Point> R(P.begin() + mid, P.end());
	
	ll minL = closestPair2(L), minR = closestPair2(R);
	merge(L.begin(), L.end(), R.begin(), R.end(), P.begin(), yCoord);

	ll res = min(minL, minR);
	vector<Point> cand; 
	for (auto& p : P) {
		if (abs(p.x - Xmid) < res)
			cand.push_back(p);
	}

	int m = (int)cand.size();
	for (int i = 0; i < m; i++) {
		for (int j = i + 1; j < m; j++) {
			ll dy = cand[j].y - cand[i].y;
			if (dy * dy >= res) { break; }
			res = min(res, dist2(cand[i], cand[j]));
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n; 
	vector<Point> points(n);
	for (auto& x : points) { cin >> x; }
	sort(points.begin(), points.end(), xCoord);

	cout << closestPair2(points) << '\n';
}