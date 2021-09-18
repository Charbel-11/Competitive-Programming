#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

struct room {
	ll l, r, a;
	vector<int> edges;
	room(ll _l, ll _r, ll _a) :l(_l), r(_r), a(_a) {}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, m; ll k; cin >> n >> m >> k;

		vector<room> rooms;
		for (int i = 0; i < n; i++) {
			ll l, r, a; cin >> l >> r >> a;
			rooms.push_back(room(l, r, a));
		}

		for (int i = 0; i < m; i++) {
			int u, v; cin >> u >> v;
			rooms[u].edges.push_back(v);
			rooms[v].edges.push_back(u);
		}

		vector<ll> maskSum(1 << n, 0);
		vector<int> maskEdges(1 << n, 0);
		for (int i = 1; i < (1 << n); i++) {
			ll cur = 0;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) { 
					cur += rooms[j].a; 

					maskEdges[i] |= (1 << j);
					for (int v : rooms[j].edges) {
						maskEdges[i] |= (1 << v);
					}
				}
			}
			maskSum[i] = cur;
		}

		vector<vector<ll>> dp((1 << n), vector<ll>(n, 0));
		for (int i = 0; i < n; i++) { dp[(1 << i)][i] = 1; }
		for (int i = 1; i < (1 << n); i++) {
			for (int j = 0; j < n; j++) {
				if (!(i & (1 << j))) { continue; }

				for (int v = 0; v < n; v++) {
					if (i & (1 << v)) { continue; }
					if (!(maskEdges[i] & (1 << v))) { continue; }
					if (maskSum[i] >= rooms[v].l && maskSum[i] <= rooms[v].r) {
						int newMask = i | (1 << v);
						dp[newMask][v] += dp[i][j];
					}
				}
			}
		}

		ll ans = 0;
		for (int i = 1; i < (1 << n); i++) {
			if (maskSum[i] != k) { continue; }
			for (int j = 0; j < n; j++) {
				ans += dp[i][j];
			}
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
