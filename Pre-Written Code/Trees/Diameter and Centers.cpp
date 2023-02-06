#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct Edge {
	int u, v; Edge() {}
	Edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct Node { vector<Edge> edges; };

struct Tree {
	vector<Node> nodes;
	int root, n;

	Tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void addEdge(int u, int v) {
		Edge e1(u, v); Edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, vector<int> &dist) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dist[e.v] = dist[u] + 1;
			dfs(e.v, u, dist);
		}
	}

	//To find all possible endpoints of the diameter, after storing all d2s such that dist2[d2] = diameter in the set of endpoints,
	//we need another dfs from any d2 (vector dist(n, -1) where dist[d2] = 0 and dfs(d2, -1, dist)) and add all i such that dist[i] = diameter
    //The idea is all such endpoints will be at the same distance from any such d2 so using just one is enough
	void findDiameter(int &diameter, int &d1, int &d2) {
		diameter = 0; d1 = d2 = root;
		vector<int> dist(n, -1);

		dist[root] = 0; dfs(root, -1, dist);
		for (int i = 0; i < n; i++) {
			if (dist[i] > diameter) { diameter = dist[i]; d1 = i; }
		}

		dist[d1] = 0; dfs(d1, -1, dist);
		for (int i = 0; i < n; i++) {
			if (dist[i] >= diameter) { diameter = dist[i]; d2 = i; }
		}
	}

	//OR find diameter, root the Tree on an endpoint, starting from the second endpoint
	//go up d/2, we get to the center (if d is odd, the next parent is the next center)
	void findCenters(int &c1, int &c2) {
		vector<int> leaves[2], cnt(n, 0);
		for (int i = 0; i < n; i++) {
			cnt[i] = nodes[i].edges.size();
			if (cnt[i] == 1) { leaves[0].push_back(i); }
		}

		bool alt = 0; int nR = n;
		while (nR > 2) {
			leaves[!alt].clear();
			for (auto &u : leaves[alt]) {
				cnt[u] = -1; nR--;
				for (auto &e : nodes[u].edges) {
					if (cnt[e.v] == -1) { continue; }
					cnt[e.v]--;
					if (cnt[e.v] == 1) { leaves[!alt].push_back(e.v); }
				}
			}
			alt = !alt;
		}

		c1 = c2 = -1;
		for (int i = 0; i < n; i++) {
			if (cnt[i] >= 0 && c1 == -1) { c1 = i; }
			else if (cnt[i] >= 0) { c2 = i; break; }
		}
	}

	//----------------------------------------------------------------------------------------------------------//

	//Finds all diameters and centers (if 2 centers exist it takes any 1) of each Tree in a forest
	vector<pair<int, int>> findDiametersAndCenters() {
		vector<pair<int, int>> ans;
		vector<bool> vis1(n, 0), vis2(n, 0);
		vector<int> parent(n, 0);
		for (int i = 0; i < n; i++) {
			if (vis1[i]) { continue; }
			int diameter, d1, d2;
			findDiameter(i, vis1, vis2, parent, diameter, d1, d2);
			int c = findCenter(d2, diameter, parent);
			ans.push_back({ diameter, c });
		}
		return move(ans);
	}

	//returns {endpoint, dist}
	pair<int, int> bfs(int u, vector<bool> &visited, vector<int> &parent) {
		queue<pair<int, int>> Q; visited[u] = true;
		int dist = 0; Q.push({ u, 0 });
		while (!Q.empty()) {
			u = Q.front().first; dist = Q.front().second; Q.pop();
			for (auto &e : nodes[u].edges) {
				if (visited[e.v]) { continue; }
				visited[e.v] = true; Q.push({ e.v, dist + 1 });
				parent[e.v] = u;
			}
		}
		return { u, dist };
	}

	void findDiameter(int u, vector<bool> &vis1, vector<bool>& vis2, vector<int> &parent,
		int &diameter, int &d1, int &d2) {
		d1 = bfs(u, vis1, parent).first;
		auto p = bfs(d1, vis2, parent);
		d2 = p.first; diameter = p.second;
	}
	//Can be modified to return both centers if the diameter is odd
	//u should be the endpoint of the diameter which is not the root (so, the Tree should be rooted at the other endpoint)
	//if above function is used, use u = d2
	int findCenter(int u, int diameter, vector<int> &parent) {
		diameter >>= 1;
		while (diameter--) { u = parent[u]; }
		return u;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	Tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.addEdge(u, v);
	}
}