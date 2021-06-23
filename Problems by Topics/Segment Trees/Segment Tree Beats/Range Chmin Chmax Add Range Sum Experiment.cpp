//https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e15;	//Change if needed

vector<ll> base;

enum Type { MIN, MAX, ADD, SET };

struct StVal {
	ll sum = 0, max1 = -INF, max2 = -INF, min1 = INF, min2 = INF;
	ll lazySet = INF;
	int freqMax = 0, freqMin = 0;
	StVal() {}
	StVal(const ll _v) {
		sum = max1 = min1 = _v;
		freqMax = freqMin = 1;
		max2 = -INF; min2 = INF;
	}
	StVal(const StVal& v1, const StVal& v2) {
		sum = v1.sum + v2.sum;
		if (v1.max1 > v2.max1) {
			max1 = v1.max1; freqMax = v1.freqMax;
			max2 = max(v1.max2, v2.max1);
		}
		else if (v1.max1 < v2.max1) {
			max1 = v2.max1; freqMax = v2.freqMax;
			max2 = max(v2.max2, v1.max1);
		}
		else {
			max1 = v1.max1; freqMax = v1.freqMax + v2.freqMax;
			max2 = max(v2.max2, v1.max2);
		}

		if (v1.min1 < v2.min1) {
			min1 = v1.min1; freqMin = v1.freqMin;
			min2 = min(v1.min2, v2.min1);
		}
		else if (v1.min1 > v2.min1) {
			min1 = v2.min1; freqMin = v2.freqMin;
			min2 = min(v2.min2, v1.min1);
		}
		else {
			min1 = v1.min1; freqMin = v1.freqMin + v2.freqMin;
			min2 = min(v1.min2, v2.min2);
		}
		lazySet = INF;
	}

	//Applies changes of type at node si using val
	void updateVal(const ll val, const Type type, const int lo, const int hi) {
		ll len = hi - lo + 1;
		if (type == MIN) {
			if (max1 == min1 || val <= min1) { updateVal(val, SET, lo, hi);	return; }
			sum += (val - max1) * freqMax;
			max1 = val; min2 = min(min2, val);
			if (lazySet != INF) { lazySet = min(lazySet, val); }
		}
		else if (type == MAX) {
			if (max1 == min1 || max1 <= val) { updateVal(val, SET, lo, hi); return; }
			sum += (val - min1) * freqMin;
			min1 = val; max2 = max(max2, val);
			if (lazySet != INF) { lazySet = max(lazySet, val); }
		}
		else if (type == ADD) {
			if (max1 != INF) { max1 += val; }
			if (max2 != -INF) { max2 += val; }
			if (min1 != -INF) { min1 += val; }
			if (min2 != INF) { min2 += val; }
			if (lazySet != INF) { lazySet += val; }
			sum += val * len;
		}
		else if (type == SET) {
			max1 = val;	max2 = -INF; freqMax = len;
			min1 = val; min2 = INF; freqMin = len;
			lazySet = INF;
			sum = val * len;
		}
	}
};

struct SegTree {
	int n;
	vector<StVal> st;
	vector<int> leaves;

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
	}

	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }

	//1) Set each element A[i] in [l, r] to be min(A[i], x)
	void updateMin(const int l, const int r, const ll minV) { if (l <= r) rangeUpdate(l, r, minV, 1, 0, n - 1, MIN); }
	//2) Set each element A[i] in [l, r] to be max(A[i], x)
	void updateMax(const int l, const int r, const ll maxV) { if (l <= r) rangeUpdate(l, r, maxV, 1, 0, n - 1, MAX); }
	//3) Set each element A[i] in [l, r] to be A[i]+x
	void updateAdd(const int l, const int r, const ll x) { if (l <= r) rangeUpdate(l, r, x, 1, 0, n - 1, ADD); }
	//4) Set each element A[i] in [l, r] to be x
	void updateSet(const int l, const int r, const ll x) { if (l <= r) rangeUpdate(l, r, x, 1, 0, n - 1, SET); }

private:
	//lo, hi indices of the actual array; si is the index of the segment tree array
	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) { st.resize(si + 1); }
			st[si] = StVal(base[lo]);			//Set the actual array here
			leaves[lo] = si;
			return;
		}
		int lC = si << 1, rC = (si << 1) | 1, mid = (lo + hi) >> 1;
		init(lC, lo, mid); init(rC, mid + 1, hi);
		st[si] = StVal(st[lC], st[rC]);
	}

	//si has correct values and already used lazy values which it will propagate
	void propagateLazy(const int si, const int lo, const int hi) {
		if (lo == hi) { st[si].lazySet = INF; return; }
		const int mid = (lo + hi) >> 1;
		if (st[si].lazySet != INF) {
			st[si << 1].updateVal(st[si].lazySet, SET, lo, mid);
			st[si << 1 | 1].updateVal(st[si].lazySet, SET, mid + 1, hi);
			st[si].lazySet = INF;
			return;
		}
		if (st[si].max1 < st[si << 1].max1) {
			st[si << 1].updateVal(st[si].max1, MIN, lo, mid);
		}
		if (st[si].max1 < st[si << 1 | 1].max1) {
			st[si << 1 | 1].updateVal(st[si].max1, MIN, mid + 1, hi);
		}
		if (st[si].min1 > st[si << 1].min1) {
			st[si << 1].updateVal(st[si].min1, MAX, lo, mid);
		}
		if (st[si].min1 > st[si << 1 | 1].min1) {
			st[si << 1 | 1].updateVal(st[si].min1, MAX, mid + 1, hi);
		}
	}

	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) { return st[si]; }

		propagateLazy(si, lo, hi);
		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	bool orCheck(const int si, const ll val, const Type type) {
		if (type == MIN) { return st[si].max1 <= val; }
		else if (type == MAX) { return st[si].min1 >= val; }
		else if (type == ADD) { return false; }
		else if (type == SET) { return false; }
	}
	bool andCheck(const int si, const ll val, Type type) {
		if (type == MIN) { return st[si].max2 <= val; }
		else if (type == MAX) { return st[si].min2 >= val; }
		else if (type == ADD) { return st[si].max2 == -INF; }
		else if (type == SET) { return true; }
	}

	void rangeUpdate(const int l, const int r, const ll val, const int si, const int lo, const int hi, const Type type) {
		if (hi < l || r < lo || orCheck(si, val, type)) { return; }
		if (l <= lo && hi <= r && andCheck(si, val, type)) {
			st[si].updateVal(val, type, lo, hi);	//Sets correct values at si + lazy values to be propagated later
		}
		else {
			propagateLazy(si, lo, hi);
			const int mid = (lo + hi) >> 1;
			rangeUpdate(l, r, val, si << 1, lo, mid, type);
			rangeUpdate(l, r, val, si << 1 | 1, mid + 1, hi, type);
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	base.resize(n); for (auto& x : base) { cin >> x; }
	SegTree st(n);
	while (q--) {
		int t, l, r; cin >> t >> l >> r; r--;
		if (t == 0) {
			ll b; cin >> b;
			st.updateMin(l, r, b);
		}
		else if (t == 1) {
			ll b; cin >> b;
			st.updateMax(l, r, b);
		}
		else if (t == 2) {
			ll b; cin >> b;
			st.updateAdd(l, r, b);
		}
		else {
			cout << st.query(l, r).sum << '\n';
		}
	}
}