#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { ll w; vector<edge> edges; node(ll _w = 0) :w(_w) {} };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> nextBLift; vector<vector<ll>> nextBLiftSum;
	vector<node> nodes;
	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = int(log2(n));
		nodes.resize(n);
		nextBLift.resize(n + 1); for (auto &x : nextBLift) { x.resize(lg2 + 2, 0); }
		nextBLiftSum.resize(n + 1); for (auto &x : nextBLiftSum) { x.resize(lg2 + 2, LLONG_MAX/2-1); }
	}

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
	}

	void addNode(int u, int p) {	
		if (nodes[p].w >= nodes[u].w) { nextBLift[u][0] = p; }
		else {
			int par = p;
			for (int i = lg2; i >= 0; i--) {
				if (nodes[nextBLift[par][i]].w < nodes[u].w)
					par = nextBLift[par][i];
			}
			nextBLift[u][0] = nextBLift[par][0];
		}

		for (int i = 1; i <= lg2; i++) {
			nextBLift[u][i] = nextBLift[nextBLift[u][i - 1]][i - 1];
		}

		if (u == p) return;

		nextBLiftSum[u][0] = nodes[nextBLift[u][0]].w;
		for (int i = 1; i <= lg2; i++) {
			if (nextBLiftSum[nextBLift[u][i - 1]][i - 1] == LLONG_MAX / 2 - 1 || nextBLiftSum[u][i - 1] == LLONG_MAX / 2 - 1)
				nextBLiftSum[u][i] = LLONG_MAX / 2 - 1;
			else
				nextBLiftSum[u][i] = nextBLiftSum[u][i - 1] + nextBLiftSum[nextBLift[u][i - 1]][i - 1];
		}
	}

	ll findSequence(int R, ll X) {
		if (nodes[R].w > X) { return 0; }
		X -= nodes[R].w;

		ll res = 1;

		for (int i = lg2; i >= 0; i--) {
			if (nextBLiftSum[R][i] <= X) {
				X -= nextBLiftSum[R][i];
				res += (1ll << i);
				R = nextBLift[R][i];
			}
		}

		return res;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int Q; ll last = 0; cin >> Q;
	tree t(Q + 2);
	int cnt = 1;
	t.nodes[0].w = LLONG_MAX / 2 - 1;
	t.nodes[1].w = 0;
	t.addNode(0, 0);
	t.addNode(1, 0);

	while (Q--) {
		int mode; ll p, q; cin >> mode >> p >> q;

		if (mode == 1) {
			ll R = p ^ last, W = q ^ last;
			cnt++; t.nodes[cnt].w = W;
			t.add_edge(R, cnt);
			t.addNode(cnt, R);
		}
		else {
			ll R = p ^ last, X = q ^ last;
			last = t.findSequence(R, X);
			cout << last << endl;
		}
	}
}