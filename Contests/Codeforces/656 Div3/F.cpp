#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
#include <set>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		vector<set<int>> adj(n);
		vector<vector<int>> leavesOf(n);

		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			adj[u].insert(v); adj[v].insert(u);
		}

		int ans = 0;
		stack<int> toCheck;
		for (int i = 0; i < n; i++) { if ((int)adj[i].size() == 1) { toCheck.push(i); } }

		while (!toCheck.empty()) {
			int i = toCheck.top(); toCheck.pop();
			if ((int)adj[i].size() != 1) { continue; }

			int p = *adj[i].begin();
			leavesOf[p].push_back(i);

			if (leavesOf[p].size() == k) {
				ans++;
				for (int j = 0; j < k; j++) {
					int cur = leavesOf[p].back(); leavesOf[p].pop_back();
					adj[p].erase(cur); adj[cur].erase(p);
				}
				if ((int)adj[p].size() == 1) { toCheck.push(p); }
			}
		}

		cout << ans << '\n';
	}
}