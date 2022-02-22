#include <iostream>
#include <vector>
using namespace std;

struct edge {
	int u, v; bool match = 0; edge() {}
	edge(int _u, int _v) : u(_u), v(_v) {}
};

struct node { vector<edge> edges; node() {} };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}
};

//Classic Problems:
//Maximum Matching - Minimum Vertex Cover
//Minimum Path Cover - Maximum Bipartite Clique
struct bipartiteGraph {
	//Matching: Set of edges that do not share a node
	//Vertex Cover: Set of nodes that cover all edges
	//Cut Capacity: Set of edges that disconnect source(L) from sink(R) upon removal
	//Independent Set: Set of nodes not connected by edges

	//Complement of vertex cover = independent Set
	//Clique in graph = Independent Set in inverse Graph
	vector<node> nodes; int n, m;
	vector<bool> Z, vis;
	vector<int> unMatched, match;

	bipartiteGraph(int _n, int _m) : n(_n), m(_m) {
		nodes.resize(n + m); Z.resize(n + m, 0);
		match.resize(n + m, -1); vis.resize(n + m, 0);
	}
	bipartiteGraph(graph &g) {   // g must be undirected
		vector<int> color(g.n, -1); int LSize = 0;
		for (int i = 0; i < g.n; i++) {		//We need to skip nodes in g that we don't want in the bipartite graph
			if (color[i] != -1) { continue; } 
			color[i] = 0; colorDfs(i, g, color, LSize);
		}

		vector<int> idx(g.n, g.n + 1);
		int curL = 0, curR = LSize;
		for (int i = 0; i < g.n; i++) {
			if (color[i] == -1) { continue; }
			if (color[i] == 0) { idx[i] = curL++; }
			else { idx[i] = curR++; }
		}

		n = LSize, m = curR - LSize;
		nodes.resize(n + m); Z.resize(n + m, 0);
		match.resize(n + m, -1); vis.resize(n + m, 0);
		for (int i = 0; i < g.n; i++)
			if (idx[i] < n) {	//To avoid double edges
				for (auto &e : g.nodes[i].edges)
					add_edge(idx[i], idx[e.v]);
			}
	}
	void colorDfs(int u, graph &g, vector<int>& color, int& LSize) {
		if (color[u] == 0) { LSize++; }
		for (auto &e : g.nodes[u].edges) {
			if (color[e.v] != -1) { continue; }
			color[e.v] = (color[u] ? 0 : 1);
			colorDfs(e.v, g, color, LSize);
		}
	}

	void add_edge(int u, int v) {
		nodes[u].edges.push_back(edge(u, v));
		nodes[v].edges.push_back(edge(v, u));
	}

	bool augment(int v) {
		if (vis[v]) { return 0; }
		vis[v] = 1;
		for (auto &e : nodes[v].edges)
			if (match[e.v] == -1 || augment(match[e.v])) {
				match[e.v] = v; match[v] = e.v;
				return 1;
			}
		return 0;
	}

	//In Bipartite Graphs (Konig's Theorem)
	//Max Matching = Min Vertex Cover = Max Flow = Min Cut
	int maxMatching() { //With Greedy initialization
		int w = 0;
		for (int x = 0; x < n; x++) {
			if (match[x] != -1) { continue; }
			for (auto &e : nodes[x].edges)
				if (match[e.v] == -1) {
					match[e.v] = x; match[x] = e.v;
					w++; break;
				}
		}
		for (int i = 0; i < n; i++) {
			if (match[i] != -1) { continue; }
			for (int j = 0; j < n; j++) { vis[j] = 0; }
			w += augment(i);
		}
		return w;
	}

	void printMaxMatching() {
		int K = maxMatching();
		for (int i = 0; i < n; i++)
			if (match[i] != -1)
				cout << i + 1 << " " << match[i] - n + 1 << endl;
	}

	void vertexCoverDFS(int u, bool m, vector<bool>& visited) {
		visited[u] = Z[u] = 1;
		for (auto &e : nodes[u].edges) {
			if (visited[e.v] || e.match == m) { continue; }
			vertexCoverDFS(e.v, e.match, visited);
		}
	}

	//Let A = {unmatched nodes}, Z = {connected component of A via alternating paths ONLY}
	//Then V = (L-Z)U(RnZ) is a minimum vertex cover (By Konig's Theorem)
	vector<pair<int, int>> vertexCover() {
		int K = maxMatching();
		for (int u = 0; u < n; u++) {
			if (match[u] == -1) { unMatched.push_back(u); continue; }
			int v = match[u];
			for (auto &e : nodes[u].edges)
				if (e.v == v) { e.match = 1; break; }
			for (auto &e : nodes[v].edges)
				if (e.v == u) { e.match = 1; break; }
		}

		vector<bool> visited(n + m, 0);
		for (auto &x : unMatched)
			if (!visited[x])
				vertexCoverDFS(x, 1, visited);

		vector<pair<int, int>> ans;
		for (int i = 0; i < n; i++)
			if (!Z[i]) { ans.push_back({ 1, i + 1 }); }
		for (int i = n; i < m + n; i++)
			if (Z[i]) { ans.push_back({ 2, i - n + 1 }); }
		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin.ignore(2); return 0;
}