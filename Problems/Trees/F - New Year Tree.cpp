//On the go LCA with dynamic diameter
//Works because the root has only 3 child (4 would create a problem) and each subtree is a binary tree

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
using namespace std;

int q;
const int N = 1000000 + 10;
const int lg2 = 20;

int depth[N];
int anc[N][lg2 + 1];

	int n;

	int len = 2;
	int l = 1, r = 2;

	void init(){
		n = 4;
		depth[1] = depth[2] = depth[3] = 1;	
	}

	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = anc[u][i];	//furthest parent found is 2^i
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				u = anc[u][i];
				v = anc[v][i];
			}
		}

		return anc[u][0];
	}

	int dist(int u, int v) {
		int lca = LCA(u, v);
		return depth[u] + depth[v] - 2 * depth[lca];
	}

	int addAt(int u) {
		anc[n][0] = anc[n + 1][0] = u;
		for (int i = 1; i < lg2; i++) {
			anc[n][i] = anc[n + 1][i] = anc[anc[n][i - 1]][i - 1];
		}
		depth[n] = depth[n + 1] = depth[u] + 1;

		int c1 = dist(n, l), c2 = dist(n, r);
		if (c1 > c2 && c1 > len) { len = c1; r = n; }
		else if (c2 > len) { len = c2; l = n; }

		n += 2;
		return len;
	}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	scanf("%d", &q);
	init();

	while (q--) {
		int u; scanf("%d", &u); u--;
		printf("%d\n", addAt(u));
	}
}