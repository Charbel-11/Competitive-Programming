#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int n, a, b;
	vector<int> path, visA, visB;

	tree(int _n, int _a, int _b) : n(_n), a(_a), b(_b) { nodes.resize(n); path.push_back(0); visA.resize(n, 0); visB.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		visA[u]++; visB[u]++;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			path.push_back(e.v);
			dfs(e.v, u);
			path.pop_back();
		}

		int m = path.size();
		if (m > a) { visA[path[m - a - 1]] += visA[path[m - 1]]; }
		if (m > b) { visB[path[m - b - 1]] += visB[path[m - 1]]; }
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int tt; cin >> tt;
	for (int qq = 1; qq <= tt; qq++) {
		int n, a, b; cin >> n >> a >> b;
		tree t(n, a, b);
		for (int i = 0; i < n - 1; i++) {
			int v; cin >> v; v--;
			t.add_edge(i + 1, v);
		}

		t.dfs(0, -1);
		double ans = 0;
		for (int i = 0; i < n; i++) {
			double pA = (double)t.visA[i] / n;
			double pB = (double)t.visB[i] / n;
			ans += pA + pB - pA * pB;
		}

		cout << "Case #" << qq << ": " << setprecision(7) << fixed << ans << '\n';
	}
}