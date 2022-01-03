#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
typedef long long ll;

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

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;

	SegTree(const int n) : n(n) {
		init(1, 0, n - 1);
		lazy.resize(st.size());
	}

	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal();			//Set the actual array here
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	void updateLazy(const int si, const int lo, const int hi) {
		lazy[si].apply(st[si], lo, hi);
		if (lo != hi) {
			lazy[si << 1] = StUpdate(lazy[si << 1], lazy[si]);
			lazy[si << 1 | 1] = StUpdate(lazy[si << 1 | 1], lazy[si]);
		}
		lazy[si] = StUpdate();
	}

	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const StUpdate u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const StUpdate& u, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) {
			lazy[si] = StUpdate(lazy[si], u);
			updateLazy(si, lo, hi);
		}
		else {
			updateLazy(si, lo, hi);
			if (hi < l || r < lo) return;
			const int mid = (lo + hi) >> 1;
			update(l, r, u, si << 1, lo, mid);
			update(l, r, u, si << 1 | 1, mid + 1, hi);
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
		}
	}
};


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

struct Line {
	int x, y1, y2, add; 
	Line() {}
	Line(int _x, int _y1, int _y2, bool _add) :x(_x), y1(_y1), y2(_y2), add(_add ? 1 : -1) {}
	bool operator <(const Line& rhs) {
		return x < rhs.x;
	}
};

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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<Rect> rectangles(n);
	for (auto& r : rectangles) { cin >> r.bl >> r.tr; }

	cout << unionArea(rectangles) << '\n';
}