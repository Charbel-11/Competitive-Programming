#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> base;

struct StVal {
	ll value = 0;
	StVal *left, *right;
	StVal() {}
	StVal(const ll _v) : value(_v) { left = right = NULL; }
	StVal(StVal* v1, StVal* v2) {
		value = *v1 + *v2;
		left = v1; right = v2;
	}
	operator ll() const { return value; }
};

struct PSSegTree {
	int n;
	vector<StVal*> versions;	//contains the root of each version, 1-based since version 0 is the empty segtree
	vector<StVal*> st;	//st[1] is the root

	PSSegTree(const int n) : n(n) { init(1, 0, n - 1); versions.push_back(st[1]); }

	void init(const int si, const int lo, const int hi) {
		if (lo == hi) {
			if (si >= (int)st.size()) st.resize(si + 1);
			st[si] = new StVal(base[lo]);
		}
		else {
			const int mid = (lo + hi) >> 1;
			init(si << 1, lo, mid);
			init(si << 1 | 1, mid + 1, hi);
			st[si] = new StVal(st[si << 1], st[si << 1 | 1]);
		}
	}

	//l and r inclusive, 0-indexed, version v
	StVal* query(const int l, const int r, const int v = 0) {
		return (l <= r && l < n && r >= 0) ? query(l, r, versions[v], 0, n - 1) : new StVal();
	}
	StVal* query(const int l, const int r, StVal* si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return si;

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si->left, lo, mid);
		if (mid < l) return query(l, r, si->right, mid + 1, hi);
		return new StVal(query(l, r, si->left, lo, mid), query(l, r, si->right, mid + 1, hi));
	}

	//PERSISTENT UPDATE
	//v version, i idx, nx new INCREMENT
	StVal* PSUpdate(int v, int i, ll nx) {
		return PSUpdate(v, 0, n - 1, i, nx, versions[v]);
	}
	StVal* PSUpdate(int v, int l, int r, int i, ll nx, StVal* cur) {
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

	int n, q; cin >> n >> q;
	base.resize(n);
	for (auto &x : base) { cin >> x; }

	PSSegTree st(n);
	vector<int> m(q + 1, 0);	//maps array num to version
	m[1] = 0; int v = 0;
	int numOfArrays = 1;

	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int k, a, x; cin >> k >> a >> x; a--;
			st.PSUpdate(m[k], a, x); v++;
			m[k] = v;
		}
		else if (op == 2) {
			int k, a, b; cin >> k >> a >> b; a--; b--;
			cout << st.query(a, b, m[k])->value << '\n';
		}
		else {
			int k; cin >> k;
			st.versions.push_back(st.versions[m[k]]); v++;
			m[++numOfArrays] = v;
		}
	}
}