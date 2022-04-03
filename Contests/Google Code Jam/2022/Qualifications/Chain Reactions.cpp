#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { ll fun = 0; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	pair<ll, ll> dfs(int u, int p) {
		vector<pair<ll, ll>> childAns;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			auto curC = dfs(e.v, u);
			childAns.push_back(curC);
		}

		if (childAns.empty()) { return { nodes[u].fun, nodes[u].fun }; }
		
		ll curChainMax = nodes[u].fun, curAns = 0;
		for (int i = 0; i < childAns.size(); i++) { curAns += childAns[i].second; }

		ll minChildChain = (*min_element(childAns.begin(), childAns.end())).first;
		if (curChainMax > minChildChain) { curAns += curChainMax - minChildChain; }
		else { curChainMax = minChildChain; }

		return { curChainMax, curAns };
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n; tree t(n + 1);
		for (int i = 1; i <= n; i++) { cin >> t.nodes[i].fun; }
		for (int i = 1; i <= n; i++) {
			int p; cin >> p;
			t.add_edge(i, p);
		}

		ll ans = t.dfs(0, -1).second;
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}