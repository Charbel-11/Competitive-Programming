#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

struct StVal {
	ll totalSum = 0, sumDpTimesMax = 0, sumDpTimesMin = 0, sumPrevDP = 0;
	ll sufMax = 0, sufMin = 0;
	StVal() {}
	StVal(const StVal& v1, const StVal& v2) { 
		totalSum = (v1.totalSum + v2.totalSum) % mod;
		sumDpTimesMax = (v1.sumDpTimesMax + v2.sumDpTimesMax) % mod;
		sumDpTimesMin = (v1.sumDpTimesMin + v2.sumDpTimesMin) % mod;
		sumPrevDP = (v1.sumPrevDP + v2.sumPrevDP) % mod;
	}
};

struct StUpdate {
	ll newMax = 0, newMin = 1e12, dpVal = -1;
	StUpdate() {}
	StUpdate(const ll nMa, const ll nMi, const ll dpV) : newMax(nMa), newMin(nMi), dpVal(dpV) {}
	StUpdate(const StUpdate& u1, const StUpdate& u2) {
		newMax = max(u1.newMax, u2.newMax);
		newMin = min(u1.newMin, u2.newMin);
		if (u2.dpVal != -1) { dpVal = u2.dpVal; }
		else { dpVal = u1.dpVal; }
	}
	void apply(StVal& sv, const int lo, const int hi) {	
		if (newMax > 0) {
			sv.totalSum -= sv.sumDpTimesMax; sv.totalSum %= mod;
			sv.sumDpTimesMax = sv.sumPrevDP * newMax; sv.sumDpTimesMax %= mod;
			sv.totalSum += sv.sumDpTimesMax; sv.totalSum %= mod;
			if (sv.totalSum < 0) { sv.totalSum += mod; }

			sv.sufMax = newMax;
		}
		if (newMin < 1e12) {
			sv.totalSum += sv.sumDpTimesMin; sv.totalSum %= mod;
			sv.sumDpTimesMin = sv.sumPrevDP * newMin; sv.sumDpTimesMax %= mod;
			sv.totalSum -= sv.sumDpTimesMin; sv.totalSum %= mod;
			if (sv.totalSum < 0) { sv.totalSum += mod; }

			sv.sufMin = newMin;
		}
		if (dpVal != -1) { 
			sv.sumPrevDP = dpVal; 
			sv.sumDpTimesMax = dpVal * sv.sufMax;
			sv.sumDpTimesMin = dpVal * sv.sufMin;
			sv.totalSum = dpVal * (sv.sufMax - sv.sufMin); sv.totalSum %= mod;
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

void getSmaller(vector<ll>& A, vector<int>& firstSmaller) {
	stack<int> S; S.push(-1);
	int n = A.size();

	for (int i = 0; i < n; i++) {
		while (S.size() > 1 && A[i] <= A[S.top()]) { S.pop(); }
		firstSmaller[i] = S.top();
		S.push(i);
	}
}

void getBigger(vector<ll>& A, vector<int>& firstBigger) {
	stack<int> S; S.push(-1);
	int n = A.size();

	for (int i = 0; i < n; i++) {
		while (S.size() > 1 && A[i] >= A[S.top()]) { S.pop(); }
		firstBigger[i] = S.top();
		S.push(i);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> A(n); for (auto& x : A) { cin >> x; }

	vector<int> firstSmaller(n, -1), firstBigger(n, -1);
	getSmaller(A, firstSmaller);
	getBigger(A, firstBigger);

	SegTree st(n + 1);
	st.update(0, 0, StUpdate(A[0], A[0], 1));

	for (int i = 1; i < n; i++) {
		st.update(firstBigger[i] + 1, i, StUpdate(A[i], 1e12, -1));
		st.update(firstSmaller[i] + 1, i, StUpdate(0, A[i], -1));
		ll curAns = st.query(0, i - 1).totalSum;
		st.update(i + 1, i + 1, StUpdate(0, 1e12, curAns));
	}

	cout << st.query(n, n).sumPrevDP << '\n';
}