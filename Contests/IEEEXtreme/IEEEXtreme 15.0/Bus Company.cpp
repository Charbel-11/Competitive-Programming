#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
using namespace std;
typedef long long ll;

vector<bool> isA;
const int sqr = 448;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct Val {
	ll sumA = 0, sumB = 0;
	ll numA = 0, numB = 0;

	void copy(Val& rhs) {
		sumA = rhs.sumA; sumB = rhs.sumB;
		numA = rhs.numA; numB = rhs.numB;
	}
};

struct node {
	Val sub, up;
	vector<edge> edges;
};

struct graph {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth;

	int root, n, lg2;
	graph(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 1.0)));
		nodes.resize(n); depth.resize(n, 0);
		anc.resize(n + 1, vector<int>(lg2 + 1, -1));
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& e : nodes[cur].edges) {
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

	int findKthParent(int u, int k) {
		int pI = 0;
		while (k) {
			if (k & 1) { u = anc[u][pI]; }
			pI++; k >>= 1;
		}
		return u;
	}

	void computeValues() {
		dfs1(0, -1);
		dfs2(0, -1, 0, 0, 0, 0);
	}

	void dfs1(int u, int p) {
		nodes[u].sub.sumA = nodes[u].sub.sumB = 0;
		if (isA[u]) { nodes[u].sub.numA = 1; }
		else { nodes[u].sub.numB = 1; }

		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs1(e.v, u);
			nodes[e.u].sub.sumA += nodes[e.v].sub.sumA + nodes[e.v].sub.numA;
			nodes[e.u].sub.sumB += nodes[e.v].sub.sumB + nodes[e.v].sub.numB;
			nodes[e.u].sub.numA += nodes[e.v].sub.numA;
			nodes[e.u].sub.numB += nodes[e.v].sub.numB;
		}
	}

	void dfs2(int u, int p, ll sumA, ll sumB, int numA, int numB) {
		nodes[u].up.sumA = sumA; nodes[u].up.sumB = sumB;
		nodes[u].up.numA = numA; nodes[u].up.numB = numB;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }

			ll curSumA = nodes[e.u].sub.sumA + sumA, curSumB = nodes[e.u].sub.sumB + sumB;
			int curNumA = nodes[e.u].sub.numA + numA, curNumB = nodes[e.u].sub.numB + numB;

			curSumA -= (nodes[e.v].sub.sumA + nodes[e.v].sub.numA);
			curSumB -= (nodes[e.v].sub.sumB + nodes[e.v].sub.numB);
			curNumA -= nodes[e.v].sub.numA; curNumB -= nodes[e.v].sub.numB;

			curSumA += curNumA; curSumB += curNumB;
			dfs2(e.v, u, curSumA, curSumB, curNumA, curNumB);
		}
	}
};

struct RMQ {
	vector<vector<int>> rmq;   //rmq[i][j] stores the index of the minimum in the range [j, j+2^i]
	vector<int> v, logb2; RMQ() {}
	RMQ(vector<int>& _v) : v(_v) { //O(nlogn) time and space
		int n = (int)v.size(); logb2.resize(n + 1, 0);
		rmq.resize(1, vector<int>(n));
		iota(rmq[0].begin(), rmq[0].end(), 0);

		for (int i = 0; (1 << i) < n + 1; i++) { logb2[1 << i] = i; } //Precomputing Logs
		for (int i = 1; i < n + 1; i++) { logb2[i] = max(logb2[i], logb2[i - 1]); }
		rmq.resize(logb2.back() + 1);

		for (int t = 1; t < (int)rmq.size(); t++) {
			rmq[t].resize(n - (1 << t) + 1);
			for (int i = 0; i <= n - (1 << t); i++) {
				int x = v[rmq[t - 1][i]], y = v[rmq[t - 1][i + (1 << (t - 1))]];
				rmq[t][i] = x < y ? rmq[t - 1][i] : rmq[t - 1][i + (1 << (t - 1))];
			}
		}
	}

	int query(int i, int j) { //O(1)
		if (i > j) { swap(i, j); }
		int k = logb2[j - i + 1];
		int x = v[rmq[k][i]], y = v[rmq[k][j - (1 << k) + 1]];
		return x < y ? rmq[k][i] : rmq[k][j - (1 << k) + 1];
	}
};

struct ETT { //Euler Tour Technique
	vector<int> tree, start, finish, d, v; ETT() {}
	ETT(graph& g, int root) : d(g.n, 0), start(g.n), finish(g.n) {
		int t = 0; init(g, root, -1, t);
	}
	void init(graph& g, int cur, int p, int& t) {
		tree.push_back(cur); start[cur] = t++;
		v.push_back(d[cur]);
		for (edge& e : g.nodes[cur].edges) {
			if (e.v == p) { continue; }
			d[e.v] = 1 + d[cur];
			init(g, e.v, cur, t);
			tree.push_back(cur); t++;
			v.push_back(d[cur]);
		}
		finish[cur] = t - 1;
	}
};

struct LCA {
	ETT ett; RMQ rmq; LCA() {}
	LCA(graph& g, int root) : ett(g, root), rmq(ett.v) {}
	int find(int i, int j) { return ett.tree[rmq.query(ett.start[i], ett.start[j])]; }
	int dist(int i, int j) { return ett.d[i] + ett.d[j] - 2 * ett.d[find(i, j)]; }
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n; cin >> n; isA.resize(n);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		isA[i] = (x == 0);
	}
	vector<bool> updatedIsA = isA;

	graph t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.preprocess(); t.computeValues();
	LCA lca(t, 0);

	vector<pair<int, bool>> changes;

	int q; cin >> q;
	while (q--) {
		int type; cin >> type;
		if (type == 1) {
			int u; cin >> u; u--;
			updatedIsA[u] = !updatedIsA[u];
			changes.push_back({ u, updatedIsA[u] });

			if (changes.size() == sqr) {
				for (auto& c : changes) { isA[c.first] = c.second; }
				changes.clear(); t.computeValues();
			}
		}
		else {
			int u, v; cin >> u >> v; u--; v--;
			if (t.depth[u] < t.depth[v]) { swap(u, v); }

			Val uSub, uUp, vSub, vUp;
			uSub.copy(t.nodes[u].sub); uUp.copy(t.nodes[u].up);
			vSub.copy(t.nodes[v].sub); vUp.copy(t.nodes[v].up);

			auto update = [&](int curU, pair<int, bool> curC, Val& sub, Val& up) {
				int curLCA = lca.find(curU, curC.first), dist = lca.dist(curU, curC.first);
				Val& toChange = (curLCA == curU ? sub : up);
				if (curC.second) {
					toChange.numA++; toChange.numB--;
					toChange.sumA += dist; toChange.sumB -= dist;
				}
				else {
					toChange.numB++; toChange.numA--;
					toChange.sumB += dist; toChange.sumA -= dist;
				}
			};

			for (auto& c : changes) {
				update(u, c, uSub, uUp);
				update(v, c, vSub, vUp);
			}

			ll curSumA = 0, curSumB = 0, numPathsA = 0, numPathsB = 0;
			if (lca.find(u, v) == v) {
				int vC = t.findKthParent(u, lca.dist(u, v) - 1);

				Val vCSub, vCUp;
				if (vC == u) {
					vCSub.copy(uSub); vCUp.copy(uUp);
				}
				else {
					vCSub.copy(t.nodes[vC].sub); vCUp.copy(t.nodes[vC].up);
					for (auto& c : changes) { update(vC, c, vCSub, vCUp); }
				}

				vSub.sumA -= (vCSub.sumA + vCSub.numA);
				vSub.sumB -= (vCSub.sumB + vCSub.numB);
				vSub.numA -= vCSub.numA; vSub.numB -= vCSub.numB;

				vSub.numA += vUp.numA; vSub.numB += vUp.numB;
				vSub.sumA += vUp.sumA; vSub.sumB += vUp.sumB;
			}

			numPathsA = uSub.numA * vSub.numA; numPathsB = uSub.numB * vSub.numB;
			curSumA = uSub.sumA * vSub.numA + vSub.sumA * uSub.numA;
			curSumB = uSub.sumB * vSub.numB + vSub.sumB * uSub.numB;

			if (numPathsA == numPathsB && numPathsA == 0) { cout << "TIE" << '\n'; continue; }
			else if (numPathsA == 0) { cout << "B" << '\n'; continue; }
			else if (numPathsB == 0) { cout << "A" << '\n'; continue; }

			curSumA *= numPathsB; curSumB *= numPathsA;
			if (curSumA < curSumB) { cout << "A" << '\n'; }
			else if (curSumB < curSumA) { cout << "B" << '\n'; }
			else { cout << "TIE" << '\n'; }
		}
	}
}