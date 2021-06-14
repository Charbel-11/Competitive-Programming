/* 
Min/Max cost bipartite matching via shortest augmenting paths
This is an O(|V|ˆ3) implementation of a shortest augmenting path
algorithm for finding min cost perfect matchings in dense graphs. 
In practice, it solves 1000x1000 problems in around 1 second.

The values in cost[i][j] may be positive or negative. 
To perform maximization, simply negate the cost[][] matrix.
*/
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
typedef long long ll;
using namespace std;

//cost[i][j] = cost for pairing left node i with right node j
//Lmate[i] = index of right node that left node i pairs with
//Rmate[j] = index of left node that right node j pairs with
ll MinCostMatching(const vector<vector<ll>>& cost, vector<ll>& Lmate, vector<ll>& Rmate) {
	int n = (int)cost.size();
	vector<ll> u(n), v(n);	//Labels for the nodes

	//Start with a feasable labeling
	for (int i = 0; i < n; i++) {
		u[i] = cost[i][0];
		for (int j = 1; j < n; j++) { u[i] = min(u[i], cost[i][j]); }
	}
	for (int j = 0; j < n; j++) {
		v[j] = cost[0][j] - u[0];
		for (int i = 1; i < n; i++) { v[j] = min(v[j], cost[i][j] - u[i]); }
	}

	//Initial matching with feasable labeling
	Lmate = vector<ll>(n, -1); Rmate = vector<ll>(n, -1);
	int mated = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Rmate[j] != -1) { continue; }
			if (cost[i][j] - u[i] - v[j] == 0){
				Lmate[i] = j; Rmate[j] = i;
				mated++; break;
			}
		}
	}

	vector<ll> dist(n), parent(n), seen(n);
	//Repeat until we get a perfect matching
	while (mated < n) {
		ll s = 0; 
		while (Lmate[s] != -1) { s++; }
		//s here is an unmatched node in L

		//Initialize Dijkstra
		fill(parent.begin(), parent.end(), -1);
		fill(seen.begin(), seen.end(), 0);
		for (int k = 0; k < n; k++) { dist[k] = cost[s][k] - u[s] - v[k]; }
		ll j = 0;
		while (true) {
			//Find min dist w.r.t. s
			j = -1;
			for (int k = 0; k < n; k++) {
				if (seen[k]) { continue; }
				if (j == -1 || dist[k] < dist[j]) { j = k; }
			}
			seen[j] = 1;

			if (Rmate[j] == -1) { break; }

			//Relax neighbors
			const ll i = Rmate[j];
			for (int k = 0; k < n; k++) {
				if (seen[k]) { continue; }
				ll new_dist = dist[j] + cost[i][k] - u[i] - v[k];
				if (dist[k] > new_dist) {
					dist[k] = new_dist;
					parent[k] = j;
				}
			}
		}

		//Improve the labeling
		for (int k = 0; k < n; k++) {
			if (k == j || !seen[k]) { continue; }
			int i = Rmate[k];
			v[k] += (dist[k] - dist[j]);
			u[i] -= (dist[k] - dist[j]);
		}
		u[s] += dist[j];

		//Augment along path
		while (parent[j] >= 0) {
			int d = parent[j];
			Rmate[j] = Rmate[d];
			Lmate[Rmate[j]] = j;
			j = d;
		}
		Rmate[j] = s; Lmate[s] = j;
		mated++;
	}

	ll ans = 0;
	for (ll i = 0; i < n; i++) { ans += cost[i][Lmate[i]]; }
	return ans;
}

ll dist(vector<ll>& v1, vector<ll>& v2) {
	return abs(v1[0] - v2[0]) + abs(v1[1] - v2[1]);
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	ll n, m; cin >> m >> n;
	vector<vector<ll>> courier(n), bottle(m);
	for (int i = 0; i < m; i++) {
		ll x, y; cin >> x >> y;
		bottle[i] = { x,y };
	}
	for (int i = 0; i < n; i++) {
		ll x, y; cin >> x >> y;
		courier[i] = { x,y };
	}

	vector<ll> res(2);
	vector<vector<ll>> costs(n + m - 1, vector<ll>(n + m - 1, 0));
	cin >> res[0] >> res[1];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			costs[i][j] = dist(res, bottle[j]) + dist(courier[i], bottle[j]);

	for (int i = n; i < n + m - 1; i++)
		for (int j = 0; j < m; j++)
			costs[i][j] = 2 * dist(res, bottle[j]);

	vector<ll> v1(n + m - 1), v2(n + m - 1);
	cout << MinCostMatching(costs, v1, v2) << '\n';
}