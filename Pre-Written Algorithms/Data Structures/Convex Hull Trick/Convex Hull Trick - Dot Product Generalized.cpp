#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = (ll)4e18;

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}

	bool operator == (const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	Point operator - (const Point& rhs) const { return Point(x - rhs.x, y - rhs.y); }
	Point operator + (const Point& rhs) const { return Point(x + rhs.x, y + rhs.y); }
	bool operator < (const Point& rhs) const {
		if (x != rhs.x) return x < rhs.x;
		return y < rhs.y;
	}

	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};

ll dotProduct(const Point& A, const Point& B) { return A.x * B.x + A.y * B.y; }
ll crossProduct(const Point& A, const Point& B) { return A.x * B.y - A.y * B.x; }

//0: Colinear; 1: Clockwise (C is to the right of (AB)); 2: Counterclockwise (C is to the left of (AB))
int orientation(const Point& A, const Point& B, const Point& C) {
	ll x = crossProduct(C - B, B - A);
	return x ? 1 + (x < 0) : 0;
}

struct ConvexHull {
	vector<Point> convexHullBot, convexHullTop;

	ConvexHull(const Point& p) : convexHullBot{ p }, convexHullTop{ p }{}
	ConvexHull(const ConvexHull& a, const ConvexHull& b) {
		convexHullBot.clear(); convexHullTop.clear();

		vector<Point> v(a.convexHullBot.size() + b.convexHullBot.size());
		merge(a.convexHullBot.begin(), a.convexHullBot.end(), b.convexHullBot.begin(), b.convexHullBot.end(), v.begin());
		for (Point& p : v) {
			while (convexHullBot.size() > 1 && orientation(convexHullBot.end()[-2], convexHullBot.end()[-1], p) != 2) {
				convexHullBot.pop_back();
			}
			convexHullBot.push_back(p);
		}

		v.clear(); v.resize(a.convexHullTop.size() + b.convexHullTop.size());
		merge(a.convexHullTop.begin(), a.convexHullTop.end(), b.convexHullTop.begin(), b.convexHullTop.end(), v.begin());
		for (Point& p : v) {
			while (convexHullTop.size() > 1 && orientation(convexHullTop.end()[-2], convexHullTop.end()[-1], p) != 1) {
				convexHullTop.pop_back();
			}
			convexHullTop.push_back(p);
		}
	}
};

// Given a set of points (Ai,Bi) and a point (x,y), finds min/max(Ai.x+Bi.y)
// Addition of points takes O(n logn) overall amortized time; a query takes O(log^2n) time
// maxCoord^2 should fit in long long
struct ConvexHullTrickDynamic {
	int numPoints = 0;
	vector<ConvexHull> hulls;

	void addPoint(ll A, ll B) {
		Point curP(A, B); numPoints++;
		hulls.emplace_back(curP);

		for (int j = 1; (j & numPoints) == 0; j <<= 1) {
			hulls.rbegin()[1] = ConvexHull(hulls.rbegin()[1], hulls.back());
			hulls.pop_back();
		}
	}

	// Finds min(Ai.x + Bi.y) in O(log^2n)
	ll getMinDotProduct(ll x, ll y) const {
		Point curP(x, y);

		auto findMin = [&](const vector<Point>& convexHullBdry) -> ll {
			int l = 0, r = convexHullBdry.size() - 1;
			while (l < r) {
				int mid1 = l + (r - l) / 3;
				int mid2 = l + 2 * ((r - l) / 3);
				if (mid2 == mid1) { mid2++; }

				if (dotProduct(curP, convexHullBdry[mid1]) < dotProduct(curP, convexHullBdry[mid2])) { r = mid2 - 1; }
				else { l = mid1 + 1; }
			}
			return dotProduct(curP, convexHullBdry[l]);
		};

		ll ans = INF;
		for (auto& hull : hulls) {
			ans = min({ ans, findMin(hull.convexHullBot), findMin(hull.convexHullTop) });
		}

		return ans;
	}

	// Finds max(Ai.x + Bi.y) in O(log^2n)
	ll getMaxDotProduct(ll x, ll y) const {
		return -getMinDotProduct(-x, -y);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);


}