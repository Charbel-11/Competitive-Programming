//https://www.spoj.com/problems/PT07J/

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int block = 320;			//Set it to sqrt(n)
int group[320];
int freqVal[(int)1e5 + 2];		//Set to the range of numbers
int startT[(int)1e5 + 2], endT[(int)1e5 + 2];
int valToNode[(int)1e5 + 2];
vector<int> order;

struct query {
	int L, R, idx, k;
	query(int l, int r, int _k, int i) : L(l), R(r), k(_k), idx(i) {}

	bool operator<(const query& q2) {
		int b1 = L / block, b2 = q2.L / block;
		if (b1 != b2) { return b1 < b2; }
		return (b1 & 1) ? (R > q2.R) : (R < q2.R);
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int val; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int p, int &t) {
		startT[u] = t; order.push_back(nodes[u].val);
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			t++; preorder(e.v, u, t);
		}
		endT[u] = t;
	}
};

//i is only an index in the array!
void add(int i) {
	int val = order[i];
	freqVal[val]++; group[val / block]++;
}

void remove(int i) {
	int val = order[i];
	freqVal[val]--; group[val / block]--;
}

int getAns(int k) {
	int b = 0;
	while (group[b] < k) { k -= group[b]; b++; }
	int v = b * block;
	while (freqVal[v] < k) { k -= freqVal[v]; v++; }
	return valToNode[v];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n); vector<int> comp;
	for (int i = 0; i < n; i++) {
		int val; cin >> val;
		t.nodes[i].val = val;
		comp.push_back(val);
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (int i = 0; i < n; i++) {
		t.nodes[i].val = lower_bound(comp.begin(), comp.end(), t.nodes[i].val) - comp.begin();
		valToNode[t.nodes[i].val] = i + 1;
	}

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	int timeStamp = 0;
	t.preorder(0, -1, timeStamp);

	int m; cin >> m;
	vector<query> queries;
	for (int i = 0; i < m; i++) {
		int x, k; cin >> x >> k; x--;
		queries.push_back(query(startT[x], endT[x], k, i));
	}
	sort(queries.begin(), queries.end());

	vector<int> ans(m);
	int L = 0, R = -1;
	for (auto &q : queries) {
		while (R < q.R) { add(++R); }
		while (L > q.L) { add(--L); }
		while (L < q.L) { remove(L++); }
		while (R > q.R) { remove(R--); }
		ans[q.idx] = getAns(q.k);
	}

	for (auto &x : ans) { cout << x << '\n'; }
}