#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct StVal {
	int remFrom = 200000, addTo = 0; StVal() {}
	StVal(const int _v) {}
	StVal(const StVal &v1, const StVal &v2) { }
};

struct StUpdate {
	int addTo = 0, remFrom = 200000; bool over = false;
	StUpdate() {}
	StUpdate(const int a, const int r, const bool _o) { addTo = a; remFrom = r; over = _o; }
	StUpdate(const StUpdate &u1, const StUpdate &u2) {
		if (u2.over) {
			over = true;
			addTo = min(max(u1.addTo, u2.addTo), u2.remFrom);
			remFrom = max(min(u1.remFrom, u2.remFrom), u2.addTo);
		}
		else { addTo = u1.addTo; remFrom = u1.remFrom; over = u1.over; }
	}
	void apply(StVal &sv, const int lo, const int hi) {	
		if (over) {
			sv.addTo = min(max(sv.addTo, addTo), remFrom);
			sv.remFrom = max(min(sv.remFrom, remFrom), remFrom);
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

	StVal query(const int l, const int r) { return (l <= r && l < n && r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
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

	void updateAllLazy() { updateAllLazy(1, 0, n - 1); }
	void updateAllLazy(const int si, const int lo, const int hi) {
		updateLazy(si, lo, hi);
		if (lo != hi) {
			const int mid = (lo + hi) >> 1;
			updateAllLazy(si << 1, lo, mid);
			updateAllLazy(si << 1 | 1, mid + 1, hi);
		}
	}

	vector<StVal> retrieve() {
		updateAllLazy();
		vector<StVal> res(n);
		for (int i = 0; i < n; ++i)
			res[i] = st[leaves[i]];
		return move(res);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	SegTree st(n);
	while (k--) {
		int type; cin >> type;
		int l, r, h; cin >> l >> r >> h;
		if (type == 1) { st.update(l, r, StUpdate(h, 200000, true)); }
		else { st.update(l, r, StUpdate(0, h, true)); }
	}

	vector<StVal> ans = st.retrieve();
	for (auto &x : ans) { cout << x.addTo << '\n'; }
}