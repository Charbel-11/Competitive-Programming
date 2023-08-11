#include <bits/stdc++.h>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void addEdge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	bool cycleDFS(int u, vector<int> &color, vector<int> &parent) {
		color[u] = 1;
		for (auto &e : nodes[u].edges) {
			int v = e.v;
			if (color[v] == 0) {
				parent[v] = u;
				if (cycleDFS(v, color, parent)) { return true; }
			}
			else if (color[v] == 1) { parent[v] = u; return true; }	//One node in the cycle would be u or v
		}
		color[u] = 2; return false;
	}
	bool hasCycle() {
		vector<int> color(n, 0), parent(n, -1);
		for (int v = 0; v < n; v++)
			if (cycleDFS(v, color, parent)) { return true; }
		return false;
	}

	void dfs(int u, vector<int> &visited, vector<int> &ans) {
		visited[u] = true;
		for (auto &e : nodes[u].edges) {
			int v = e.v;
			if (!visited[v]) { dfs(v, visited, ans); }
		}
		ans.push_back(u);
	}
	vector<int> topologicalSort() {
		vector<int> visited(n, false), ans;
		for (int i = 0; i < n; ++i)
			if (!visited[i]) { dfs(i, visited, ans); }
		reverse(ans.begin(), ans.end());
		return ans;
	}

	//Returns the lexicographically smallest top sort (need the in-degree of each node)
	vector<int> minTopSort() {
		priority_queue<int, vector<int>, greater<int>> Q; vector<int> ans;
		for (int i = 0; i < n; i++) {
			if (nodes[i].inD == 0) { Q.push(i); }
		}
		while (!Q.empty()) {
			int cur = Q.top(); Q.pop();
			ans.push_back(cur);
			for (auto& e : nodes[cur].edges) {
				nodes[e.v].inD--;
				if (nodes[e.v].inD == 0) { Q.push(e.v); }
			}
		}
		return ans;
	}

	//Call topSort before or call it in the function and remove the parameter
	int longestPath(vector<int>& topSort) {
		vector<int> DP(n, 0);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (auto &e : nodes[topSort[i]].edges) {
				DP[e.v] = max(DP[e.v], DP[e.u] + 1);
				ans = max(ans, DP[e.v]);
			}
		}
		return ans;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

}