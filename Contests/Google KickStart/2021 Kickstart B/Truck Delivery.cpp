#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll; //In case ll is used, be sure to change everything (StVal/update function/vectors...)
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
vector<ll> ans;

struct StVal {
	ll v = 0; StVal() {}
	StVal(const ll _v) : v(_v) {}
	StVal(const StVal& v1, const StVal& v2) { v = gcd(v1, v2); }
	operator ll() const { return v; }	
};

struct SegTree {
	int n;
	vector<int> leaves;
	vector<StVal> st;	//st[1] root; To go to a child, *2 (l) or *2+1 (r);	To go to a parent: /2

	SegTree(const int n) : n(n) {
		leaves.resize(n);
		init(1, 0, n - 1);
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

	//l and r inclusive, 0-indexed
	StVal query(const int l, const int r) { return (l <= r && l < n&& r >= 0) ? query(l, r, 1, 0, n - 1) : StVal(); }
	StVal query(const int l, const int r, const int si, const int lo, const int hi) {
		if (l <= lo && hi <= r) return st[si];

		const int mid = (lo + hi) >> 1;
		if (r <= mid) return query(l, r, si << 1, lo, mid);
		if (mid < l) return query(l, r, si << 1 | 1, mid + 1, hi);
		return StVal(query(l, r, si << 1, lo, mid), query(l, r, si << 1 | 1, mid + 1, hi));
	}

	//Change a leaf and update its ancestors' values
	void update(const int i, ll c) {
		int si = leaves[i];
		st[si] = StVal(c);
		for (si >>= 1; si; si >>= 1)
			st[si] = StVal(st[si << 1], st[si << 1 | 1]);
	}
};


const ll INF = 1e17;
struct edge {
	int u, v, L; ll A; edge() {}
	edge(int _u, int _v, int _l, ll _a) :
		u(_u), v(_v) , L(_l), A(_a) {}
};

struct node { vector<pair<int, int>> queries; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v, int L, ll A) {
		edge e1(u, v, L, A); edge e2(v, u, L, A);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, SegTree& st) {
		for (auto& q : nodes[u].queries) {
			ans[q.first] = st.query(0, q.second);
		}

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			ll prev = st.query(e.L, e.L);
			st.update(e.L, gcd(prev, e.A));
			dfs(e.v, e.u, st);
			st.update(e.L, prev);
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int tt; cin >> tt;
	for (int qq = 1; qq <= tt; qq++) {
		int n, q; cin >> n >> q;
		ans.clear(); ans.resize(q);
		tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			int l; ll A; cin >> l >> A;
			t.add_edge(u, v, l, A);
		}

		for (int i = 0; i < q; i++) {
			int c, w; cin >> c >> w; c--;
			t.nodes[c].queries.push_back({ i,w });
		}

		SegTree st(2e5 + 5);
		t.dfs(0, -1, st);

		cout << "Case #" << qq << ": ";
		for (auto& x : ans) { cout << x << ' '; } cout << '\n';
	}
}