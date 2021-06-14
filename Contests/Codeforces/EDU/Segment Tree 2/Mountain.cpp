#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <algorithm>
using namespace std;

struct StVal {
	int maxP = 0, sum = 0; StVal() {}
	StVal(const int _v) : maxP(_v), sum(_v) {}
	StVal(const StVal &v1, const StVal &v2) {
		sum = v1.sum + v2.sum;
		maxP = max(v1.maxP, v1.sum + v2.maxP);
	}
};

struct StUpdate {
	int v = 0; bool c = false; StUpdate() {}
	StUpdate(const int v, const bool _c) : v(v), c(_c) {}
	StUpdate(const StUpdate &u1, const StUpdate &u2) {
		if (u2.c) { c = 1; v = u2.v; }
		else { c = u1.c; v = u1.v; }
	}
	void apply(StVal &sv, const int lo, const int hi) {
		if (c) {
			sv.sum = v * (hi - lo + 1);
			sv.maxP = (v > 0 ? sv.sum : v);
		}
	}
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<StUpdate> lazy;
	vector<int> leaves;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
		lazy.resize(st.size());
	}

	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal();			//Set the actual array here
			leaves[lo] = si;
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

	int query(const int h) { return query(h, 1, 0, n - 1); }
	int query(const int h, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);

		if (st[si].maxP <= h) { return -1; }
		if (lo == hi) { return lo; }

		const int mid = (lo + hi) >> 1;
		int c1 = query(h, si << 1, lo, mid);
		if (c1 != -1) { return c1; }
		return query(h - st[si << 1].sum, si << 1 | 1, mid + 1, hi);
	}

	StVal queryS(const int l, const int r) { return (l <= r && l < n && r >= 0) ? queryS(l, r, 1, 0, n - 1) : StVal(); }
	StVal queryS(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return queryS(l, r, si << 1, lo, mid);
		if (mid < l) return queryS(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(queryS(l, r, si << 1, lo, mid), queryS(l, r, si << 1 | 1, mid + 1, hi));
	}

	void update(const int l, const int r, const StUpdate u) { if (l <= r) update(l, r, u, 1, 0, n - 1); }
	void update(const int l, const int r, const StUpdate &u, const int si, const int lo, const int hi) {
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

struct query {
	bool update;
	int a, b, D, h;

	query(int _a, int _b, int _D) : a(_a), b(_b), D(_D), update(true) {}
	query(int _h) :h(_h), update(false) {}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;

	vector<query> queries; vector<int> comp; comp.push_back(0);

	char type; cin >> type;
	while (type != 'E') {
		if (type == 'I') {
			int a, b, D; cin >> a >> b >> D;
			queries.push_back(query(a, b, D));
			comp.push_back(a); comp.push_back(b);
			comp.push_back(a - 1); comp.push_back(b + 1);
		}
		else {
			int h; cin >> h;
			queries.push_back(h);
		}

		cin >> type;
	}

	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	SegTree st(comp.size() + 1);
	vector<int> history(comp.size() + 1, 0);
	set<int> lastUsed; lastUsed.insert(0);
	map<int, int> startPoints;

	for (query &q : queries) {
		if (q.update) {
			int a = lower_bound(comp.begin(), comp.end(), q.a) - comp.begin();
			int b = lower_bound(comp.begin(), comp.end(), q.b) - comp.begin();
			st.update(a, a, StUpdate(q.D, true));
			if (a != b) {
				st.update(b, b, StUpdate(q.D*(q.b - q.a), true));
				st.update(a + 1, b - 1, StUpdate(0, true));
			}
			history[a] = history[b] = q.D;

			auto it = lastUsed.lower_bound(a);
			auto it2 = lastUsed.upper_bound(b);
			if (it != lastUsed.end() && *it <= b) { lastUsed.erase(it, it2); }
			lastUsed.insert(a); lastUsed.insert(b);

			auto it3 = startPoints.lower_bound(a);
			auto it4 = startPoints.upper_bound(b);
			if (it3 != startPoints.end() && it3->first <= b) { startPoints.erase(it3, it4); }
			startPoints[a] = b;

			auto prevv = prev(lastUsed.lower_bound(a));
			if (startPoints.count(*prevv) && startPoints[*prevv] != *prevv) {
				if (a - 1 != *prevv) {
					int DD = history[*prevv];
					st.update(a - 1, a - 1, StUpdate(DD*(comp[a - 1] - comp[*prevv]), true));
					history[a - 1] = DD; lastUsed.insert(a - 1);
				}
				startPoints[*prevv] = a - 1;
			}

			auto nxtt = lastUsed.upper_bound(b);
			if (nxtt != lastUsed.end() && !startPoints.count(*nxtt)) {
				int DD = history[*nxtt];
				st.update(b + 1, b + 1, StUpdate(DD, true));
				history[b + 1] = DD; lastUsed.insert(b + 1);
				if (*nxtt != b + 1) { st.update(*nxtt, *nxtt, StUpdate(DD*(comp[*nxtt] - comp[b + 1]), true)); }
				startPoints[b + 1] = *nxtt;
			}
		}
		else {
			int ans = st.query(q.h);
			if (ans == -1) { cout << n << '\n'; continue; }
			if (ans == 0) { cout << 0 << '\n';	continue; }
			if (startPoints.count(ans)) { cout << comp[ans] - 1 << '\n'; continue; }

			int pp = *prev(lastUsed.lower_bound(ans));
			int prev = comp[pp], prefS = st.queryS(0, pp).sum, H = q.h, D = history[ans];
			H -= prefS;

			int k = (H + 1 + D - 1) / D;
			cout << prev + k - 1 << '\n';
		}
	}
}