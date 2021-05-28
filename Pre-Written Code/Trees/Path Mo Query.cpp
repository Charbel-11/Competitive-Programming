#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int block = 320;			//Set it to sqrt(n)
int freqNode[(int)1e5 + 2], freqVal[(int)1e5 + 2];		//Set to the range of numbers
int startT[(int)1e5 + 2], endT[(int)1e5 + 2];			//Set to n
vector<int> orderM;
int curAns;

struct query {
	int L, R, idx, extra;
	query(int l, int r, int i) : L(l), R(r), idx(i), extra(-1) {}

	bool operator<(const query& q2) {
		int b1 = L / block, b2 = q2.L / block;
		if (b1 != b2) { return b1 < b2; }
		return R < q2.R;
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) : u(_u), v(_v) {}
};

struct node { int w; vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth;

	int root, n, lg2;

	tree() {}
	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n); depth.resize(n, 0);
		anc.resize(n + 1); for (auto &x : anc) { x.resize(lg2 + 1, -1); }
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	//Need to call this first
	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur;
				depth[e.v] = depth[cur] + 1;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++)
			for (int u = 0; u < n; u++)
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = anc[u][i];	//furthest parent found is 2^i
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				u = anc[u][i];
				v = anc[v][i];
			}
		}

		return anc[u][0];
	}

	void modifiedDfs(int u, int p, int &t) {
		startT[u] = t;
		orderM.push_back(u);
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			t++; modifiedDfs(e.v, u, t);
		}
		t++; endT[u] = t;
		orderM.push_back(u);
	}
};

tree t;
void add(int i) {
	int curNode = orderM[i]; int w = t.nodes[curNode].w;
	freqNode[curNode]++;
	if (freqNode[curNode] == 2) {
		freqVal[w]--; 
		if (freqVal[w] == 0) { curAns--; }
	}
	else if (freqNode[curNode] == 1) {
		freqVal[w]++;
		if (freqVal[w] == 1) { curAns++; }
	}
}

void remove(int i) {
	int curNode = orderM[i]; int w = t.nodes[curNode].w;
	freqNode[curNode]--;
	if (freqNode[curNode] == 1) {
		freqVal[w]++;
		if (freqVal[w] == 1) { curAns++; }
	}
	else if (freqNode[curNode] == 0) {
		freqVal[w]--;
		if (freqVal[w] == 0) { curAns--; }
	}
}

int addExtra(int i) {
	if (i == -1) { return 0; }
	int curNode = orderM[i]; int w = t.nodes[curNode].w;
	return freqVal[w] == 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int N, M; cin >> N >> M;
	t = tree(N); vector<int> comp;
	for (int i = 0; i < N; i++) {
		int ww; cin >> ww;
		t.nodes[i].w = ww;
		comp.push_back(ww);
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (int i = 0; i < N; i++) {
		t.nodes[i].w = lower_bound(comp.begin(), comp.end(), t.nodes[i].w) - comp.begin();
	}

	for (int i = 0; i < N - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	int timeStamp = 0;
	t.modifiedDfs(0, -1, timeStamp);
	t.preprocess();

	vector<query> queries;
	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v; u--; v--;
		if (startT[u] > startT[v]) { swap(u, v); }
		int lca = t.LCA(u, v);
		if (lca == u) { queries.push_back(query(startT[u], startT[v], i)); }
		else {
			queries.push_back(query(endT[u], startT[v], i));
			queries.back().extra = startT[lca];
		}
	}
	sort(queries.begin(), queries.end());

	vector<int> ans(M);
	int L = 0, R = -1;
	for (auto &q : queries) {
		while (R < q.R) { add(++R); }
		while (L > q.L) { add(--L); }
		while (L < q.L) { remove(L++); }
		while (R > q.R) { remove(R--); }
		int add = addExtra(q.extra);		//Counted in the answer but not in the range
		ans[q.idx] = curAns + add;
	}

	for (auto &x : ans) { cout << x << '\n'; }
}