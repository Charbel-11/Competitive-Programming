//https://codeforces.com/contest/786/problem/C

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct StVal {
	int value = 0;
	StVal *left, *right;
	StVal() {}
	StVal(const int _v) : value(_v) { left = right = NULL; }
	StVal(StVal* v1, StVal* v2) {
		value = *v1 + *v2;
		left = v1; right = v2;
	}
	operator int() const { return value; }
};

struct PSSegTree {
	int n;
	vector<StVal*> versions;	//contains the root of each version
	vector<StVal*> st;	//st[1] is the root

	PSSegTree(const int n) : n(n) { init(1, 0, n - 1); versions.push_back(st[1]); }

	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) st.resize(si + 1);
			st[si] = new StVal();
		}
		else {
			const int mid = (lo + hi) >> 1;
			init(si << 1, lo, mid);
			init(si << 1 | 1, mid + 1, hi);
			st[si] = new StVal(st[si << 1], st[si << 1 | 1]);
		}
	}

	//l and r inclusive, 0-indexed, version v
	StVal* queryS(const int l, const int r, const int v = 0) {
		return (l <= r && l < n && r >= 0) ? queryS(l, r, versions[v], 0, n - 1) : new StVal();
	}
	StVal* queryS(const int l, const int r, StVal* si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return si;

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return queryS(l, r, si->left, lo, mid);
		if (mid < l) return queryS(l, r, si->right, mid + 1, hi);
		return new StVal(queryS(l, r, si->left, lo, mid), queryS(l, r, si->right, mid + 1, hi));
	}

	int query(int k, const int v = 0) { return query(k, versions[v], 0, n - 1); }
	int query(int k, StVal* si, const int lo, const int hi) {
		if (k > si->value) { return n; }
		if (lo == hi) { return lo; }

		const int mid = (lo + hi) >> 1;
		if (si->left->value < k) { return query(k - si->left->value, si->right, mid + 1, hi); }
		else { return query(k, si->left, lo, mid); }
	}

	//PERSISTENT UPDATE
	//v version, i idx, nx new val
	StVal* PSUpdate(int v, int i, int nx) { return PSUpdate(v, 0, n - 1, i, nx, versions[v]); }
	StVal* PSUpdate(int v, int l, int r, int i, int nx, StVal* cur) {
		if (l == r) {
			StVal* nv = new StVal(nx);
			if (l == 0 && r == n - 1) { versions.push_back(nv); }
			return nv;
		}
		if (l == r - 1) {
			StVal* nv = new StVal(nx), *par;
			if (i == l) { par = new StVal(nv, cur->right); }
			else { par = new StVal(cur->left, nv); }
			if (l == 0 && r == n - 1) { versions.push_back(nv); }
			return par;
		}
		int m = (l + r) >> 1;
		if (i <= m) {
			StVal* nl = PSUpdate(v, l, m, i, nx, cur->left);
			StVal* nv = new StVal(nl, cur->right);
			if (l == 0 && r == n - 1) { versions.push_back(nv); }
			return nv;
		}
		else {
			StVal* nr = PSUpdate(v, m + 1, r, i, nx, cur->right);
			StVal* nv = new StVal(cur->left, nr);
			if (l == 0 && r == n - 1) { versions.push_back(nv); }
			return nv;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	vector<int> occ(n + 1, -1), ltov(n);
	PSSegTree st(n); int v = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (occ[nums[i]] != -1) {
			st.PSUpdate(v, occ[nums[i]], 0); v++;
		}
		st.PSUpdate(v, i, 1); v++;

		occ[nums[i]] = i; ltov[i] = v;
	}

	for (int k = 1; k <= n; k++) {
		int l = 0, res = 0;
		while (l < n) {
			int r = st.query(k + 1, ltov[l]); r--;
			res++; l = r + 1;
		}
		cout << res << ' ';
	}
	cout << '\n';
}