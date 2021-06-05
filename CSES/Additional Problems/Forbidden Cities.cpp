#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <math.h>
#include <stack>
using namespace std;

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}

	bool operator ==(edge& o) {
		return (o.u == u && o.v == v && o.w == w);
	}
};

struct node {
	bool artPt = false; vector<int> edges;
	node() {}
	node(bool b) : artPt(b) {}
};

struct graph {
	vector<node> nodes;
	vector<edge> edges;
	vector<vector<int>> anc;
	vector<int> depth;
	int root, n, lg2;

	graph(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 1.0)));
		nodes.resize(n);
		anc.resize(n + 1); for (auto& x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
	}

	int add_node(bool artPt = false) {
		nodes.push_back(node(artPt)); 
		n++; return n - 1;
	}

	void resizeVectors() {
		lg2 = (int)(ceil(log2(n + 1.0)));
		anc.resize(n + 1); for (auto& x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
	}

	void add_edge(int u, int v, int w = 0) {
		nodes[u].edges.emplace_back(edges.size());
		edges.emplace_back(u, v, w);
		nodes[v].edges.emplace_back(edges.size());
		edges.emplace_back(v, u, w);
	}

	//tin[u] = discovery time of u
	//low[u] = lowest discovery time of a reachable node
	void artPointDFS(int cur, int p, vector<int>& low, vector<int>& tin,
		vector<int>& treeIdx, int& timer, int cnt, stack<edge>& S, vector<vector<edge>>& comp) {
		treeIdx[cur] = cnt; tin[cur] = low[cur] = timer++; int c = 0;
		for (auto& x : nodes[cur].edges) {
			edge& e = edges[x];	if (e.v == p) { continue; }
			if (treeIdx[e.v] == -1 || tin[e.u] > tin[e.v]) { S.push(e); }
			if (treeIdx[e.v] != -1) { low[cur] = min(low[cur], tin[e.v]); continue; }

			artPointDFS(e.v, cur, low, tin, treeIdx, timer, cnt, S, comp);
			low[cur] = min(low[cur], low[e.v]); c++;
			if (p != -1 && low[e.v] >= tin[cur]) { nodes[cur].artPt = true; }
			if (low[e.v] >= tin[cur]) {
				comp.push_back(vector<edge>());
				while (true) {
					edge& curE = S.top(); S.pop();
					comp.back().push_back(curE);
					if (curE == e) { break; }
				}
			}
		}
		if (p == -1 && c > 1) { nodes[cur].artPt = true; }
	}

	//Finds the biconnected components in the component of u
	vector<vector<edge>> findBiComponents(int u, int cnt, vector<int>& treeIdx) {
		int timer = 0; vector<int> low(n, -1), tin(n, -1);
		stack<edge> S; vector<vector<edge>> comp;
		artPointDFS(u, -1, low, tin, treeIdx, timer, cnt, S, comp);
		return move(comp);
	}

	//Builds a forest with 2 types of nodes: compressed bi-components and articulation points
	//Each tree corresponds to one component in g
	//treeIdx[i] is the tree idx of node i
	//comp[i] is the idx of the biconnected component/art point that contains i in the block tree treeIdx[i]
	vector<graph> buildBlockTrees(vector<int>& treeIdx, vector<int>& comp) {
		treeIdx.clear(); treeIdx.resize(n, -1);
		comp.clear(); comp.resize(n, -1);
		vector<graph> forest; int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (treeIdx[i] != -1) { continue; }
			vector<vector<edge>> edges = findBiComponents(i, cnt++, treeIdx);
			graph curG(0);
			for (auto& biComp : edges) {
				int id = curG.add_node();
				for (auto& e : biComp) {
					for (auto& x : { e.u, e.v }) {
						if (nodes[x].artPt) {
							if (comp[x] == -1) { comp[x] = curG.add_node(true); }
							curG.add_edge(id, comp[x]);
						}
						else { comp[x] = id; }
					}
				}
			}
			if (edges.empty()) { comp[i] = curG.add_node(); }  //Isolated vertex
			curG.resizeVectors();
			forest.emplace_back(curG);
		}
		return move(forest);
	}

	//Copy the constructor
	//Need to call this first
	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto& eIdx : nodes[cur].edges) {
				auto& e = edges[eIdx];
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

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[lca];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, q; cin >> n >> m >> q;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<int> treeIdx, comp;
	graph blockTree = g.buildBlockTrees(treeIdx, comp)[0];
	blockTree.preprocess();
	while (q--) {
		int a, b, c; cin >> a >> b >> c; a--; b--; c--;
		if (a == c || b == c) { cout << "NO\n"; continue; }
		set<int> used;
		a = comp[a]; b = comp[b]; c = comp[c];
		used.insert(a); used.insert(b); used.insert(c);
		if (used.size() < 3) { cout << "YES\n"; continue; }

		if (blockTree.nodes[c].artPt && blockTree.dist(a, b) == blockTree.dist(a, c) + blockTree.dist(c, b)) {
			cout << "NO\n"; continue;
		}
		cout << "YES\n";
	}
}