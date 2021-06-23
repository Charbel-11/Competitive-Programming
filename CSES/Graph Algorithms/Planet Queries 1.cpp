#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, q; cin >> n >> q;
	int lg = 32;
	vector<vector<int>> anc(n, vector<int>(lg));

	for (int i = 0; i < n; i++) {
		int v; cin >> v; v--;
		anc[i][0] = v;
	}

	for (int i = 1; i < lg; i++)
		for (int u = 0; u < n; u++)
			anc[u][i] = anc[anc[u][i - 1]][i - 1];

	while (q--) {
		int v, k; cin >> v >> k; v--;
		int pow = 0;
		while (k) {
			if (k & 1) { v = anc[v][pow]; }
			k >>= 1; pow++;
		}
		cout << v + 1 << '\n';
	}
}