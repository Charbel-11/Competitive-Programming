//https://www.spoj.com/problems/MKTHNUM/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct StVal {
	int value = 0;
	StVal* left = NULL, * right = NULL;
	StVal() {}
	StVal(const int _v) : value(_v) { left = right = NULL; }
	StVal(StVal* v1, StVal* v2) {	//v1, v2 are never NULL
		value = *v1 + *v2;
		left = v1; right = v2;
	}
	operator int() const { return value; }
};

struct PSSegTree {
	int n;
	vector<StVal*> versions;	//contains the root of each version, 1-based since version 0 is the empty segtree
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

	int query(const int l, const int r, int k) {
		return query(k, versions[l], versions[r + 1], 0, n - 1);
	}
	int query(int k, StVal* si1, StVal* si2, const int lo, const int hi) {
		if (lo == hi) { return lo; }

		const int mid = (lo + hi) >> 1;
		int leftNum = si2->left->value - si1->left->value;
		if (leftNum >= k) { return query(k, si1->left, si2->left, lo, mid); }
		return query(k - leftNum, si1->right, si2->right, mid + 1, hi);
	}

	//PERSISTENT UPDATE
	//v version, i idx, nx new val
	StVal* PSUpdate(int v, int i, int nx) {
		return PSUpdate(0, n - 1, i, nx, versions[v]);
	}
	StVal* PSUpdate(int l, int r, int i, int nx, StVal* cur) {
		if (l == r) {
			StVal* nv = new StVal(nx);
			if (l == 0 && r == n - 1) { versions.push_back(nv); }
			return nv;
		}
		int m = (l + r) >> 1;
		if (i <= m) {
			StVal* nl = PSUpdate(l, m, i, nx, cur->left);
			StVal* par = new StVal(nl, cur->right);
			if (l == 0 && r == n - 1) { versions.push_back(par); }
			return par;
		}
		else {
			StVal* nr = PSUpdate(m + 1, r, i, nx, cur->right);
			StVal* par = new StVal(cur->left, nr);
			if (l == 0 && r == n - 1) { versions.push_back(par); }
			return par;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> comp, a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i]; comp.push_back(a[i]);
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	PSSegTree st(n); int v = 0;
	for (int i = 0; i < n; i++) {
		a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin();
		st.PSUpdate(v, a[i], 1); v++;
	}

	while (m--) {
		int l, r, k; cin >> l >> r >> k; l--; r--;
		cout << comp[st.query(l, r, k)] << '\n';
	}
}