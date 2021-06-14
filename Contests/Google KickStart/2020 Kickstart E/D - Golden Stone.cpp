#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	for (int qq = 1; qq <= t; qq++) {
		int N, M, S, R; cin >> N >> M >> S >> R;
		int n = N * S;
		vector<vector<int>> adj(n);
		for (int i = 0; i < M; i++) {
			int u, v; cin >> u >> v;
			u--; v--; u *= S; v *= S;
			for (int k = 0; k < S; k++) {
				adj[u + k].push_back(v + k);
				adj[v + k].push_back(u + k);
			}
		}

		vector<ll> dist(n, INF);
		for (int i = 0; i < N; i++) {
			int c; cin >> c;
			while (c--) {
				int curS; cin >> curS; curS--;
				dist[i*S + curS] = 0;
			}
		}

		vector<vector<int>> stoneToRecipe(S);
		vector<int> product(R), numIng(R);

		for (int i = 0; i < R; i++) {
			cin >> numIng[i];
			for (int j = 0; j < numIng[i]; j++) {
				int x; cin >> x; x--;
				stoneToRecipe[x].push_back(i);
			}
			cin >> product[i]; product[i]--;
		}

		priority_queue <pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
		vector<int> recipeCount(N*R, 0); vector<ll> recipeDist(N*R, 0);

		vector<bool> visited(N*S, false);

		for (int i = 0; i < n; i++) { if (dist[i] == 0)  pq.push({ 0ll,i }); }

		while (!pq.empty()) {
			ll d = pq.top().first; int cur = pq.top().second; pq.pop();
			//BAD, without !pq.empty() check got TLE
			//while (!pq.empty() && visited[cur]) { d = pq.top().first; cur = pq.top().second; pq.pop(); }
			//if (visited[cur]) { break; }
			if (visited[cur]) { continue; }
			visited[cur] = true;

			int curN = cur / S, curS = cur % S;
			for (auto &r : stoneToRecipe[curS]) {
				int idx = curN * R + r;
				recipeCount[idx]++; recipeDist[idx] += dist[cur];
				if (recipeCount[idx] == numIng[r]) {
					ll newD = recipeDist[idx]; int newN = curN * S + product[r];
					if (dist[newN] > newD) {
						dist[newN] = newD;
						pq.push({ dist[newN], newN });
					}
				}
			}

			for (auto &v : adj[cur])
				if (dist[v] > dist[cur] + 1) {
					dist[v] = dist[cur] + 1;
					pq.push({ dist[v], v });
				}
		}

		ll ans = INF;
		for (int i = 0; i < N; i++) { ans = min(ans, dist[i*S]); }

		cout << "Case #" << qq << ": " << (ans >= 1e12 ? -1 : ans) << '\n';
	}
}