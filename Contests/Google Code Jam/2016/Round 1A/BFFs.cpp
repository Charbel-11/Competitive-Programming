#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	int cycleNode; set<int> in2C;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v);
		nodes[u].edges.push_back(e1);
	}

	bool cycle_dfs(int u, vector<int> &color, vector<int> &parent) {
		color[u] = 1;
		for (auto x : nodes[u].edges) {
			int v = x.v;
			if (color[v] == 0) {
				parent[v] = u;
				if (cycle_dfs(v, color, parent)) { return true; }
			}
			else if (color[v] == 1) { parent[v] = u; cycleNode = v; return true; }
		}
		color[u] = 2; return false;
	}
	int find_cycle() {
		int ans = 0;
		vector<int> color(n, 0), parent(n, -1);
		set<pair<int, int>> m;
		for (int v = 0; v < n; v++) {
			if (cycle_dfs(v, color, parent)) {
				int length = 0, cur = cycleNode;
				while (cur != -1 && parent[cur] != cycleNode) { length++; cur = parent[cur]; }
				if (cur != -1) {
					if (length == 1) {
						int other = nodes[cycleNode].edges[0].v;
						in2C.insert(other); in2C.insert(cycleNode);
						if (m.count({ other, cycleNode }) == 0)
							m.insert({ cycleNode, other });
					}
					ans = max(ans, length + 1);
				}
			}
		}

		vector<int> leaves;
		for (int v = 0; v < n; v++) {
			if (parent[v] == -1) { leaves.push_back(v); }
		}

		vector<int> visited(n, 0);
		vector<int> add(n, 0);
		for (auto &x : leaves) {
			pair<int, int> p = depth(x, parent, visited);
			if (p.second == -1) { continue; }
			add[p.second] = max(add[p.second], p.first);
		}

		int c2 = m.size() * 2;
		for (int i = 0; i < n; i++) { c2 += add[i]; }
		ans = max(ans, c2);
		return ans;
	}

	pair<int, int> depth(int x, vector<int>& parent, vector<int>& visited) {
		visited[x] = true;
		int nb = nodes[x].edges[0].v;
		if (in2C.count(nb)) { return { 1,nb }; }
		if (visited[nb]) { return { 0,-1 }; }
		pair<int, int> p = depth(nb, parent, visited);
		return { 1 + p.first, p.second };
	}
};

int main() {
	ifstream ifs("in.in");
	ofstream ofs("out.txt");
	int T; ifs >> T;
	for (int z = 0; z < T; z++) {
		int n; ifs >> n;
		graph g(n);
		for (int i = 0; i < n; i++) {
			int v; ifs >> v; v--;
			g.add_edge(i, v);
		}

		ofs << "Case #" << z + 1 << ": " << g.find_cycle() << endl;
	}
}