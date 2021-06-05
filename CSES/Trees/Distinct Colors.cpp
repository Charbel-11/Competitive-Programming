#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int block = 320;		//Set it to sqrt(n)
int freq[(int)2e5 + 5];		//Set to the range of numbers
int curAns;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int c; vector<edge> edges; };

vector<int> start, finish, order;
struct tree {
	vector<node> nodes;
	int n;

	tree(int _n) : n(_n) { nodes.resize(n); start.resize(n, -1); finish.resize(n, -1); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preorder(int u, int &t) {
		start[u] = t; t++; order.push_back(nodes[u].c);
		for (auto &x : nodes[u].edges) {
			if (start[x.v] == -1) { preorder(x.v, t); }
		}
		finish[u] = t - 1;
	}
};

struct query {
	int L, R, idx;
	query(int l, int r, int i) : L(l), R(r), idx(i) {}

	bool operator<(const query& q2) {
		int b1 = L / block, b2 = q2.L / block;
		if (b1 != b2) { return b1 < b2; }
		return (b1 & 1) ? (R > q2.R) : (R < q2.R);
	}
};

//i is only an index in the array!
void add(int i) {
	freq[order[i]]++;
	if (freq[order[i]] == 1) { curAns++; }
}

void remove(int i) {
	freq[order[i]]--;
	if (freq[order[i]] == 0) { curAns--; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<int> comp;
	int n; cin >> n; tree t(n);
	for (int i = 0; i < n; i++) { cin >> t.nodes[i].c; comp.push_back(t.nodes[i].c); }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (int i = 0; i < n; i++) { t.nodes[i].c = lower_bound(comp.begin(), comp.end(), t.nodes[i].c) - comp.begin(); }
	int tS = 0; t.preorder(0, tS);

	vector<query> queries;
	for (int i = 0; i < n; i++) {
		int l = start[i], r = finish[i];
		queries.push_back(query(l, r, i));
	}
	sort(queries.begin(), queries.end());

	vector<int> ans(n);
	int L = 0, R = -1;
	for (auto &q : queries) {
		while (R < q.R) { add(++R); }
		while (L > q.L) { add(--L); }
		while (L < q.L) { remove(L++); }
		while (R > q.R) { remove(R--); }
		ans[q.idx] = curAns;
	}

	for (auto &x : ans) { cout << x << ' '; }cout << '\n';
}