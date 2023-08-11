#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

//0: Colinear; 1: Clockwise (C is to the right of (AB)); 2: Counterclockwise (C is to the left of (AB))
int orientation(const Point& A, const Point& B, const Point& C) {
	ll x = crossProduct(C - B, B - A);
	return x ? 1 + (x < 0) : 0;
}

// Given a set of points (Ai,Bi) added with increasing/decreasing Ai and a point (x,y), finds min/max(Ai.x+Bi.y)
// Additions and queries run in O(log n)
// We can always swap Bi and Ai if we have points with increasing/decreasing Bi
// maxCoord^2 should fit in long long
struct ConvexHullTrick {
	vector<Point> convexHullBot, convexHullTop;

	void addPoint(ll A, ll B) {
		Point curP(A, B);
		while (convexHullBot.size() > 1 && orientation(convexHullBot.end()[-2], convexHullBot.end()[-1], curP) != 2) {
			convexHullBot.pop_back();
		}
		while (convexHullTop.size() > 1 && orientation(convexHullTop.end()[-2], convexHullTop.end()[-1], curP) != 1) {
			convexHullTop.pop_back();
		}
		convexHullBot.push_back(curP); convexHullTop.push_back(curP);
	}

	// Finds min(Ai.x + Bi.y) in O(logn)
	ll getMinDotProduct(ll x, ll y) const {
		Point curP(x, y);

		auto findMinIdx = [&](const vector<Point>& convexHull) -> int {
			int l = 0, r = convexHull.size() - 1;
			while (l < r) {
				int mid1 = l + (r - l) / 3;
				int mid2 = l + 2 * ((r - l) / 3);
				if (mid2 == mid1) { mid2++; }

				if (dotProduct(curP, convexHull[mid1]) < dotProduct(curP, convexHull[mid2])) { r = mid2 - 1; }
				else { l = mid1 + 1; }
			}
			return l;
		};

		int minBot = findMinIdx(convexHullBot), minTop = findMinIdx(convexHullTop);
		return min(dotProduct(curP, convexHullBot[minBot]), dotProduct(curP, convexHullTop[minTop]));
	}

	// Finds max(Ai.x + Bi.y) in O(logn)
	ll getMaxDotProduct(ll x, ll y) const {
		return -getMinDotProduct(-x, -y);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);


}