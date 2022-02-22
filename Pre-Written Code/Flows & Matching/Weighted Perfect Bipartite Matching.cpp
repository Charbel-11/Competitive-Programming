/*
Min/Max cost bipartite matching via shortest augmenting paths
This is an O(|V|^3) implementation of a shortest augmenting path
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

//cost[i][j] = cost for pairing left node i with right node j (cost is an nxn matrix)
//matchL[i] = index of right node that left node i pairs with
//matchR[j] = index of left node that right node j pairs with
ll MinCostPerfectMatching(const vector<vector<ll>>& cost, vector<int>& matchL, vector<int>& matchR) {
	int n = (int)cost.size();
	vector<ll> pL(n, 0), pR(n, 0);

	//Start with compatible prices
	for (int i = 0; i < n; i++) {
		pL[i] = -cost[i][0];
		for (int j = 1; j < n; j++) { pL[i] = max(pL[i], -cost[i][j]); }
	}
	for (int j = 0; j < n; j++) {
		pR[j] = cost[0][j] + pL[0];
		for (int i = 1; i < n; i++) { pR[j] = min(pR[j], cost[i][j] + pL[i]); }
	}

	//Initial matching
	matchL = vector<int>(n, -1); matchR = vector<int>(n, -1);
	int mated = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (matchR[j] != -1) { continue; }
			if (pL[i] + cost[i][j] - pR[j] == 0) {
				matchL[i] = j; matchR[j] = i;
				mated++; break;
			}
		}
	}

	vector<ll> dist(n); vector<int> parent(n), seen(n);
	while (mated < n) {
		int s = 0;
		while (matchL[s] != -1) { s++; }

		fill(parent.begin(), parent.end(), -1);
		fill(seen.begin(), seen.end(), 0);
		for (int k = 0; k < n; k++) { dist[k] = pL[s] + cost[s][k] - pR[k]; }

		int curMinR = 0;
		while (true) {
			curMinR = -1;
			for (int k = 0; k < n; k++) {
				if (seen[k]) { continue; }
				if (curMinR == -1 || dist[k] < dist[curMinR]) { curMinR = k; }
			}
			seen[curMinR] = 1;

			if (matchR[curMinR] == -1) { break; }		// Found a shortest augmenting path

			const int curL = matchR[curMinR];
			for (int nextR = 0; nextR < n; nextR++) {
				if (seen[nextR]) { continue; }
				ll new_dist = dist[curMinR] + pL[curL] + cost[curL][nextR] - pR[nextR];
				if (dist[nextR] > new_dist) {
					dist[nextR] = new_dist;
					parent[nextR] = curMinR;
				}
			}
		}

		for (int k = 0; k < n; k++) {
			if (k == curMinR || !seen[k]) { continue; }
			pR[k] += (dist[k] - dist[curMinR]);
			pL[matchR[k]] += (dist[k] - dist[curMinR]);
		}
		pL[s] -= dist[curMinR];

		int curR = curMinR;
		while (parent[curR] >= 0) {
			int p = parent[curR];
			matchR[curR] = matchR[p];
			matchL[matchR[curR]] = curR;
			curR = p;
		}
		matchR[curR] = s; matchL[s] = curR;
		mated++;
	}

	ll ans = 0;
	for (int i = 0; i < n; i++) { ans += cost[i][matchL[i]]; }
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

}