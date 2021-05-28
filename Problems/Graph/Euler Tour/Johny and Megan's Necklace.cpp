//https://codeforces.com/contest/1361/problem/C
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<int> edges; };

//Goes over all edges, not necessarily all vertices
struct graph {
	vector<edge> edges;
	vector<node> nodes;
	int n, m;
	graph(int _n) : n(_n), m(0) { nodes.resize(n); }

	void add_edge(int u, int v) {
		nodes[u].edges.push_back(m);
		nodes[v].edges.push_back(m);
		edges.push_back(edge(u, v)); m++;
	}

	//Start can be any node; if it has to be 0 we should hard code it
	//Since node 0 could have 0 edges and start becomes 1 for ex
	vector<pair<int, pair<int, bool>>> euler_undirected() {
		int start = -1, odd_deg = 0;
		for (int i = 0; i < n; ++i) {
			if ((int)nodes[i].edges.size() & 1) { odd_deg++; start = i; }
			else if (!nodes[i].edges.empty() && start == -1) { start = i; }
		}

		if (odd_deg > 0) { return vector<pair<int, pair<int, bool>>>(); } //Euler tour/cycle not possible
		vector<bool> used(m, 0);
		vector<pair<int, pair<int, bool>>> stack, res;
		vector<int> which(n + 1, 0);		//which[v] = index of the edge with endpoint v to check next

		stack.push_back({ start, {-1, 0} });
		while (!stack.empty()) {
			int v = stack.back().first; int eId = stack.back().second.first; bool b = stack.back().second.second;
			while (which[v] < (int)nodes[v].edges.size() && used[nodes[v].edges[which[v]]]) { which[v]++; }
			if (which[v] == (int)nodes[v].edges.size()) {
				stack.pop_back(); res.push_back({ v, {eId, b} });
			}
			else {
				int ed = nodes[v].edges[which[v]];
				used[ed] = 1;
				if (edges[ed].u == v)
					stack.push_back({ edges[ed].v, {ed, 0} });
				else 
					stack.push_back({ edges[ed].u, {ed, 1}});
			}
		}
		if (count(used.begin(), used.end(), false)) { return vector<pair<int, pair<int, bool>>>(); }	//Not all edges were reachable
		reverse(res.begin(), res.end());
		return move(res);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n; cin >> n;
	vector<pair<int, int>> neck(n);
	for (auto &p : neck) { cin >> p.first >> p.second; }

	int ans = 0; vector<pair<int, pair<int, bool>>> path;
	for (int b = 20; b > 0; b--) {
		int N = 1 << b;
		int mask = N - 1;
		graph g(N);
		for (int i = 0; i < n; i++) {
			int curU = neck[i].first & mask, curV = neck[i].second & mask;
			g.add_edge(curU, curV);
		}

		path = g.euler_undirected();
		if (!path.empty()) { ans = b; break; }
	}

	cout << ans << '\n';
	if (ans == 0) {
		for (int i = 1; i <= n; i++) { cout << 2 * i - 1 << ' ' << 2 * i << ' '; }
		return 0;
	}
	for (int i = 1; i < (int)path.size(); i++) {
		int curU = (path[i].second.first + 1) * 2 - 1;
		int curV = curU + 1;

		if (path[i].second.second) { swap(curU, curV); }
		cout << curU << ' ' << curV << ' ';
	}
}