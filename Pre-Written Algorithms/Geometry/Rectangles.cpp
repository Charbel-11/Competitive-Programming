#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi = 3.14159265358979323846;

struct Point {
	ll x, y; Point() {}
	Point(ll _x, ll _y) : x(_x), y(_y) {}
	Point(const Point& rhs) : x(rhs.x), y(rhs.y) {}
	friend istream& operator >> (istream& is, Point& p) { is >> p.x >> p.y; return is; }
};
struct Rect {
	Point bl, tr;	//(x1,y1) bot left point and (x2,y2) top right point
	Rect() {}
	Rect(ll _x1, ll _y1, ll _x2, ll _y2) : bl(_x1, _y1), tr(_x2, _y2) {}
	ll area() { return (tr.y - bl.y) * (tr.x - bl.x); }
};

ll intersectArea(const Rect& r1, const Rect& r2) {
	ll xOverlap = max(0ll, min(r1.tr.x, r2.tr.x) - max(r1.bl.x, r2.bl.x));
	ll yOverlap = max(0ll, min(r1.tr.y, r2.tr.y) - max(r1.bl.y, r2.bl.y));
	return xOverlap * yOverlap;
}
Rect intersectRect(const Rect& r1, const Rect& r2) {
	ll x1 = max(r1.bl.x, r2.bl.x), x2 = min(r1.tr.x, r2.tr.x);
	ll y1 = max(r1.bl.y, r2.bl.y), y2 = min(r1.tr.y, r2.tr.y);
	if (x1 > x2 || y1 > y2) { return Rect(0, 0, 0, 0); }
	else { return Rect(x1, y1, x2, y2); }
}

// UNION AND INTERSECTION OF MULTIPLE RECTANGLES

struct StVal {
	int mi = 0, numMin = 1; StVal() {}
	StVal(const int _v) : mi(_v), numMin(1) {}
	StVal(const StVal& v1, const StVal& v2) {
		if (v1.mi < v2.mi) { mi = v1.mi; numMin = v1.numMin; }
		else if (v1.mi > v2.mi) { mi = v2.mi; numMin = v2.numMin; }
		else { mi = v1.mi; numMin = v1.numMin + v2.numMin; }
	}
};
struct StUpdate {
	int v = 0; StUpdate() {}
	StUpdate(const int v) : v(v) {}
	StUpdate(const StUpdate& u1, const StUpdate& u2) { v = u1 + u2; }
	operator int() const { return v; }
	void apply(StVal& sv, const int lo, const int hi) {
		sv.mi += this->v;
	}
};

struct Line {
	int x, y1, y2, add;
	Line() {}
	Line(int _x, int _y1, int _y2, bool _add) :x(_x), y1(_y1), y2(_y2), add(_add ? 1 : -1) {}
	bool operator <(const Line& rhs) {
		return x < rhs.x;
	}
};

// Returns the area of the union of the rectangles
// Runs in O(maxX log(maxY))
ll unionArea(vector<Rect> rectangles) {
	int offset = 1e6;	// to avoid neg numbers
	int maxX = 0, maxY = 0;
	vector<Line> lines;
	for (auto& r : rectangles) {
		r.bl.x += offset; r.bl.y += offset;
		r.tr.x += offset; r.tr.y += offset;

		maxX = max(maxX, (int)r.tr.x);
		maxY = max(maxY, (int)r.tr.y);

		lines.push_back(Line(r.bl.x, r.bl.y, r.tr.y - 1, true));
		lines.push_back(Line(r.tr.x, r.bl.y, r.tr.y - 1, false));
	}
	sort(lines.begin(), lines.end());

	SegTree st(maxY + 1);
	int lineIdx = 0; ll ans = 0;
	for (int i = 0; i <= maxX; i++) {
		StVal curQ = st.query(0, maxY);
		if (curQ.mi != 0) { ans += maxY + 1; }
		else { ans += (maxY + 1 - curQ.numMin); }

		while (lineIdx < lines.size() && lines[lineIdx].x == i) {
			st.update(lines[lineIdx].y1, lines[lineIdx].y2, lines[lineIdx].add);
			lineIdx++;
		}
	}

	return ans;
}
//Assumes at most 2 rectangles intersect together
ll intersectionArea(vector<Rect> rectangles) {
	ll res = 0;
	for (auto& r : rectangles) { res += r.area(); }
	res -= unionArea(rectangles);
	return res;
}