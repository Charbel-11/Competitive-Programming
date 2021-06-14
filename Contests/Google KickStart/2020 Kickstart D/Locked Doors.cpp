#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> subtreeS;
	vector<vector<int>> anc;
	int root, n, lg;

	tree(int _n, int _r = 0) : n(_n), root(_r) { 
		nodes.resize(n); subtreeS.resize(n, 1);
		lg = (int)log2(n) + 2;
		anc.resize(n, vector<int>(lg + 1, root));
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		if (p == -1) { anc[u][0] = u; }
		else { anc[u][0] = p;  }

		for (int k = 1; k <= lg; k++) {
			anc[u][k] = anc[anc[u][k - 1]][k - 1];
		}

		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			subtreeS[u] += subtreeS[e.v];
		}
	}

	int find(int u, int k, bool l) {
		if (subtreeS[u] >= k) {
			if (l) { 
				if (u >= k) { return u - k + 1; }
				k -= u; return u + k;
			}
			else {
				if (n - u >= k) { return u + k; }
				k -= (n - u);
				return u - k + 1;
			}
		}
		
		int cur = u;
		for (int i = lg; i >= 0; i--) {
			if (subtreeS[anc[cur][i]] < k) { cur = anc[cur][i]; }
		}
		if (subtreeS[cur] < k) { cur = anc[cur][0]; }

		if (nodes[cur].edges.size() == 1) { return cur; }
		if (cur < u) {
			int r = nodes[cur].edges[1].u;
			if (r == cur) { r = nodes[cur].edges[1].v; }

			k -= subtreeS[r];
			return cur - k + 1;			
		}
		else {
			int l = nodes[cur].edges[0].u;
			if (l == cur) { l = nodes[cur].edges[0].v; }

			k -= subtreeS[l];
			return cur + k;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n, q; cin >> n >> q;
		vector<int> doors(n - 1);
		for (auto &x : doors) { cin >> x; }

		cout << "Case #" << qq << ": ";

		vector<int> leftB(n - 1, -1), rightB(n - 1, -1);
		stack<pair<int, int>> S; int root = 0, curM = -1;

		for (int i = 0; i < n - 1; i++) {
			while (!S.empty() && doors[i] > S.top().first) { S.pop(); }
			if (!S.empty()) { leftB[i] = S.top().second; }
			S.push({ doors[i], i });
			if (doors[i] > curM) { curM = doors[i]; root = i; }
		}

		while (!S.empty()) { S.pop(); }
		for (int i = n - 2; i >= 0; i--) {
			while (!S.empty() && doors[i] > S.top().first) { S.pop(); }
			if (!S.empty()) { rightB[i] = S.top().second; }
			S.push({ doors[i], i });
		}
		
		tree t(n - 1, root);
		for (int i = 0; i < n - 1; i++) {
			if (rightB[i] == -1 && leftB[i] == -1) { continue; }
			else if (rightB[i] == -1) { t.add_edge(i, leftB[i]); }
			else if (leftB[i] == -1) { t.add_edge(i, rightB[i]); }
			else {
				if (doors[leftB[i]] > doors[rightB[i]]) { t.add_edge(i, rightB[i]); }
				else { t.add_edge(i, leftB[i]); }
			}
		}

		t.dfs(root, -1);

		while(q--){
			int s, k; cin >> s >> k; s--; k--;
			int node = -1; bool l = 1;
			if (s == 0) { node = 0; l = 0; }
			else if (s == n - 1) { node = n - 2; }
			else { node = doors[s - 1] > doors[s] ? s : s - 1; if (node == s) { l = 0; } }

			cout << t.find(node, k, l) + 1 << ' ';
		}
		cout << '\n';
	}
}