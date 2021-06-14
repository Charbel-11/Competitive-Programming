//Could have been done by working with the leaves
//Start by putting all leaves in a stack
//query on two leaves, if the lca is one of them this is the root
//otherwise, remove both leaves by going over their neighbors and removing themselves from their neighbor's adjacency set
//If the neighbor is now a leaf, push it to the stack
//If the stack remains with 1 element, the whole tree has exactly 1 node left: this is the root

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <unordered_set>
#include <math.h>
using namespace std;
typedef long long ll;
vector<bool> tried, possible;

const ll INF = 1e17;
struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; unordered_set<int> neighbors; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> bLift;
	vector<node> nodes;
	vector<int> depth, size;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = int(log2(n));
		nodes.resize(n);
		bLift.resize(n + 1); for (auto &x : bLift) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0);
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		nodes[u].neighbors.insert(v);
		nodes[v].neighbors.insert(u);
	}

	//Preprocessing takes O(nlogn) time
	//First call p should be equal to u
	//Copy the constructor lines
	void dfs(int u, int p) {
		bLift[u][0] = p;

		for (int i = 1; i <= lg2; i++)
			bLift[u][i] = bLift[bLift[u][i - 1]][i - 1];

		for (auto e : nodes[u].edges) {
			if (e.v == p) { continue; }

			depth[e.v] = 1 + depth[u];
			dfs(e.v, u);
		}
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = bLift[u][i];
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (bLift[u][i] != bLift[v][i]) {
				u = bLift[u][i];
				v = bLift[v][i];
			}
		}

		return bLift[u][0];
	}


	void query(int u) {
		int option1 = -1, option2 = -1;
		for (int j = 0; j < n; j++) {
			if (j == u || !possible[j]) { continue; }
			option2 = j;
			if (tried[j]) { continue; }

			option1 = j;
			if (nodes[u].neighbors.count(j) == 0) {
				cout << "? " << u + 1 << " " << j + 1 << endl; cout.flush();
				int lca; cin >> lca; lca--;
				tried[u] = tried[j] = true;
				updatePossible(u, j, lca);
				return;
			}
		}

		if (option1 != -1) {
			int j = option1;
			cout << "? " << u + 1 << " " << j + 1 << endl; cout.flush();
			int lca; cin >> lca; lca--;
			tried[u] = tried[j] = true;
			updatePossible(u, j, lca);
			return;
		}

		if (option2 != -1) {
			int j = option2;
			cout << "? " << u + 1 << " " << j + 1 << endl; cout.flush();
			int lca; cin >> lca; lca--;
			tried[u] = tried[j] = true;
			updatePossible(u, j, lca);
			return;
		}

		tried[u] = true;
	}

	void updatePossible(int u, int v, int lca) {
		if (u == v) { return; }
		if (u == lca || v == lca) {
			if (depth[u] < depth[v]) { swap(u, v); }
			if (u != lca) { possible[u] = false; }
			else { possible[v] = false; }

			int realLca = LCA(u, v);
			if (realLca == v) {
				int cur = bLift[u][0];
				while (cur != v) {
					possible[cur] = false;
					cur = bLift[cur][0];
				}
				return;
			}
			
			possible[realLca] = false;

			int cur = bLift[u][0];
			while (cur != realLca && cur != -1) {
				possible[cur] = false;
				cur = bLift[cur][0];
			}

			cur = bLift[v][0];
			while (cur != realLca && cur != -1) {
				possible[cur] = false;
				cur = bLift[cur][0];
			}
			return;
		}

		updatePossible(u, lca, lca);
		updatePossible(v, lca, lca);
	}
};


int main() {
	int n; cin >> n;
	tree t(n);

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.dfs(0,0);
	/*
	if (n == 2) {
		cout << "? 1 2" << endl;
		cout.flush();
		int lca; cin >> lca;
		cout << "! " << lca << endl;
		cout.flush();
		return 0;
	}

	if (n == 3) {
		if (t.nodes[0].neighbors.size() == 2) {
			cout << "? 2 3" << endl; cout.flush();
			int lca; cin >> lca;
			cout << "! " << lca << endl; cout.flush();
		}
		else if (t.nodes[1].neighbors.size() == 2) {
			cout << "? 1 3" << endl; cout.flush();
			int lca; cin >> lca;
			cout << "! " << lca << endl; cout.flush();
		}
		else {
			cout << "? 1 2" << endl; cout.flush();
			int lca; cin >> lca;
			cout << "! " << lca << endl; cout.flush();
		}
		return 0;
	}
	*/

	int count = 0;
	possible.resize(n, 1); tried.resize(n, 0);
	for (int i = 0; i < n; i++) {
		if (!possible[i] || tried[i]) { continue; }
		t.query(i); count++;
		if (count >= n / 2) { break; }
	}

	if (count < n / 2) {
		for (int i = 0; i < n; i++) {
			if (!possible[i]) { continue; }
			t.query(i); count++;
			if (count >= n / 2) { break; }
		}
	}

	for (int i = 0; i < n; i++) {
		if (possible[i]) { cout << "! " << i + 1 << endl; cout.flush(); return 0; }
	}
}