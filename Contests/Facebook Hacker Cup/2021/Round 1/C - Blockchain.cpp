#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <array>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

vector<ll> edgeAns;

struct DSU {
	vector<int> rank, parent;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct edge {
	int u, v, idx, c; edge() {}
	edge(int _u, int _v, int _c, int _idx) :
		u(_u), v(_v), c(_c), idx(_idx) {}

	bool operator <(const edge& rhs) { return c < rhs.c; }
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<array<ll, 20>> dp;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); dp.resize(n); }

	void add_edge(int u, int v, int c, int i) {
		edge e1(u, v, c, i); edge e2(v, u, c, i);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs1(int u, int p) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs1(e.v, u);
			
			for (int i = 0; i < 20; i++) {
				if (e.c >= i) { dp[u][i] += dp[e.v][i]; dp[u][i] %= mod; }
				else { dp[u][e.c] += dp[e.v][i]; dp[u][e.c] %= mod; }
			}
			dp[u][e.c] += 1; dp[u][e.c] %= mod;
		}
	}

	void dfs2(int u, int p) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }

			//remove contribution of e.v
			for (int i = 0; i < 20; i++) {
				if (e.c >= i) {
					dp[u][i] -= dp[e.v][i]; dp[u][i] %= mod;
					if (dp[u][i] < 0) { dp[u][i] += mod; }
				}
				else {
					dp[u][e.c] -= dp[e.v][i]; dp[u][e.c] %= mod;
					if (dp[u][e.c] < 0) { dp[u][e.c] += mod; }
				}
			}
			dp[u][e.c] -= 1; if (dp[u][e.c] < 0) { dp[u][e.c] += mod; }

			//compute answer of e
			edgeAns[e.idx] = 0;

			ll sumU = 1, sumV = 1;
			for (int i = 0; i < 20; i++) {
				sumV += dp[e.v][i]; sumU += dp[u][i];
				sumV %= mod; sumU %= mod;
			}
			for (int i = 0; i < e.c; i++) {
				ll curVal = dp[e.v][i] * sumU; curVal %= mod;
				curVal += dp[u][i] * sumV; curVal %= mod;
				curVal -= dp[u][i] * dp[e.v][i]; curVal %= mod;
				if (curVal < 0) { curVal += mod; }
				curVal *= (i + 1ll); curVal %= mod;
				edgeAns[e.idx] += curVal; edgeAns[e.idx] %= mod;

				sumV -= dp[e.v][i]; sumU -= dp[u][i];
				sumV %= mod; sumU %= mod;
				if (sumV < 0) { sumV += mod; }
				if (sumU < 0) { sumU += mod; }
			}

			ll curVal = (sumU * sumV) % mod;
			curVal *= (e.c + 1ll); curVal %= mod;
			edgeAns[e.idx] += curVal; edgeAns[e.idx] %= mod;

			//reroot to v
			for (int i = 0; i < 20; i++) {
				if (e.c >= i) { dp[e.v][i] += dp[u][i]; dp[e.v][i] %= mod; }
				else { dp[e.v][e.c] += dp[u][i]; dp[e.v][e.c] %= mod; }
			}
			dp[e.v][e.c] += 1; dp[e.v][e.c] %= mod;
			dfs2(e.v, u);

			//rollback
			for (int i = 0; i < 20; i++) {
				if (e.c >= i) {
					dp[e.v][i] -= dp[u][i]; dp[e.v][i] %= mod;
					if (dp[e.v][i] < 0) { dp[e.v][i] += mod; }
				}
				else {
					dp[e.v][e.c] -= dp[u][i]; dp[e.v][e.c] %= mod;
					if (dp[e.v][e.c] < 0) { dp[e.v][e.c] += mod; }
				}
			}
			dp[e.v][e.c] -= 1; if (dp[e.v][e.c] < 0) { dp[e.v][e.c] += mod; }

			for (int i = 0; i < 20; i++) {
				if (e.c >= i) { dp[u][i] += dp[e.v][i]; dp[u][i] %= mod; }
				else { dp[u][e.c] += dp[e.v][i]; dp[u][e.c] %= mod; }
			}
			dp[u][e.c]++; dp[u][e.c] %= mod;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		tree t(n);

		vector<edge> edges;
		for (int i = 0; i < n - 1; i++) {
			int u, v, c; ifs >> u >> v >> c; u--; v--; c--;
			t.add_edge(u, v, c, i);
			edges.push_back(edge(u, v, c, i));
		}

		ll fullAns = 0;
		DSU dsu(n); sort(edges.rbegin(), edges.rend());
		int j = 0; ll prevCnt = 0;
		for (int c = 19; c >= 0; c--) {
			ll curCnt = 0;
			while (j < n - 1 && edges[j].c == c) {
				dsu.merge(edges[j].u, edges[j].v);
				j++;
			}

			vector<bool> used(n, 0);
			for (int i = 0; i < n; i++) {
				int cur = dsu.find(i);
				if (!used[cur]) {
					used[cur] = true;

					ll curSize = dsu.size(cur);
					curCnt += (curSize * (curSize - 1)) / 2ll;
				}
			}

			ll curVal = (curCnt - prevCnt) * (c + 1ll); curVal %= mod;
			fullAns += curVal; fullAns %= mod;
			prevCnt = curCnt;
		}

		edgeAns.clear(); edgeAns.resize(n - 1, 0);
		t.dfs1(0, -1);
		t.dfs2(0, -1);

		ll ans = 1;
		for (int i = 0; i < n - 1; i++) {
			ll cur = (fullAns - edgeAns[i]) % mod;
			if (cur < 0) { cur += mod; }
			ans *= cur; ans %= mod;
		}

		if (ans < 0) { ans += mod; }
		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}