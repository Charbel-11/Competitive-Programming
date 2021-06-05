#include <vector>
#include <string>
#include <assert.h>
#include <iostream>
using namespace std;
typedef long long ll;

struct FT {
	int n;
	vector<ll> vals;
	FT(const int n) :
		n(n), vals(vector<ll>(n + 1, 0)) {
	}

	//Adds x
	void update(int i, const ll x) {
		for (++i; i <= n; i += i & -i)
			vals[i] += x;
	}
	ll query(int i) const { // sum from 0 ... i
		assert(i >= -1 && i < n);
		ll sum = 0;
		for (++i; i; i -= i & -i)
			sum += vals[i];
		return sum;
	}
	ll query(int i, int j) const {		// sum from i ... j
		return query(j) - query(i - 1);
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

vector<int> start, finish, order; vector<ll> val, pathSum;
struct tree {
	vector<node> nodes;
	int n;

	tree(int _n) : n(_n) { nodes.resize(n); start.resize(n, -1); finish.resize(n, -1); val.resize(n, 0); pathSum.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int p, int &t) {
		start[u] = t; t++; order.push_back(u);
		pathSum[u] = (p == -1 ? 0 : pathSum[p]) + val[u];
		for (auto &x : nodes[u].edges) {
			if (x.v == p) { continue; }
			preorder(x.v, u, t);
		}
		finish[u] = t - 1;
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	tree t(n);
	for (int i = 0; i < n; i++) { cin >> val[i]; }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	int tS = 0; t.preorder(0, -1, tS);

	FT st(n + 1); st.update(0, val[0]);
	for (int i = 1; i < n; i++) { st.update(i, pathSum[order[i]] - pathSum[order[i - 1]]); }

	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int s; ll k; cin >> s >> k; s--;
			ll newVal = k - val[s];
			val[s] = k;
			st.update(start[s], newVal);
			st.update(finish[s] + 1, -newVal);
		}
		else {
			int s; cin >> s; s--;
			cout << st.query(start[s]) << '\n';
		}
	}
}