#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		ll S = 0;
		vector<ll> w(n); for (auto& x : w) { cin >> x; S += x; }

		vector<int> adj(n, 0);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			adj[u]++; adj[v]++;
		}

		vector<pair<ll, int>> values;
		for (int i = 0; i < n; i++) {
			if (!(adj[i] == 1)) { values.push_back({ w[i], i }); }
		}
		sort(values.begin(), values.end());

		for (int i = 1; i <= n - 1; i++) {
			cout << S << ' ';
			if (!values.empty()) {
				pair<ll, int> p = values.back();
				S += p.first;
				adj[p.second]--;
				if (adj[p.second] == 1) { values.pop_back(); }
			}
		}
		cout << '\n';
	}
}