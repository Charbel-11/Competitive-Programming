#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> anc;
vector<bool> vis;
vector<int> len;    //len[i] = dist from i to the start of the cycle (the start could be any point on the cycle)

void dfs(int s) {
    if (vis[s]) { return; }
    vis[s] = 1;
    dfs(anc[s][0]);
    len[s] = len[anc[s][0]] + 1;
}
int toKth(int x, int k) {
    if (k <= 0) { return x; }
    int i = 0;
    while (k) {
        if (k & 1) { x = anc[x][i]; }
        k >>= 1; i++;
    }
    return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, q; cin >> n >> q;
	int lg = 32;
	anc.resize(n, vector<int>(lg));
    vis.resize(n, 0); len.resize(n, 0);

	for (int i = 0; i < n; i++) {
		int v; cin >> v; v--;
		anc[i][0] = v;
	}

	for (int i = 1; i < lg; i++)
		for (int u = 0; u < n; u++)
			anc[u][i] = anc[anc[u][i - 1]][i - 1];

    for (int i = 0; i < n; i++) {
        if (!vis[i]) { dfs(i); }
    }
    while (q--) {
        int u, v; cin >> u >> v; u--; v--;
        int cycleU = toKth(u, len[u]);
        int cycleV = toKth(v, len[v]);
        if (cycleU != cycleV) { cout << -1 << '\n'; continue; }
        if (toKth(u, len[u] - len[v]) == v) { cout << len[u] - len[v] << '\n'; continue; }
        if (toKth(cycleU, len[cycleU] - len[v]) == v) { cout << len[u] + len[cycleU] - len[v] << '\n'; continue; }
        cout << -1 << '\n';
    }
}