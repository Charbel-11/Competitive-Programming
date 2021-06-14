#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <queue>
#include <climits>

using namespace std;

int dp[500002][2];
vector<int> res;

vector<vector<int>> adj;

int findMax(int u, bool b, int p) {
	if (dp[u][b] != -1) { return dp[u][b]; }

	int ans = 0;
	for (auto &v : adj[u]) {
		if (v == p) {continue; }
		if (!b) { findMax(v, 1, u); };
		ans += findMax(v, 0, u);
	}

	int ss = ans;
	if (!b) {
		for (auto &v : adj[u]) {
			if (v == p) { continue; }
			int given = 1 + dp[v][1], notGiven = dp[v][0];
			int cur = ss - notGiven + given;
			ans = max(ans, cur);
		}
	}

	return dp[u][b] = ans;
}

void back(int u, bool b, int p) {
	int ss = 0;
	for (auto &v : adj[u]) {
		if (v == p) { continue; }
		ss += dp[v][0];
	}
	
	int choice = -1;
	if (!b && ss != dp[u][b]) {
		for (auto &v : adj[u]) {
			if (v == p) { continue; }
			int given = 1 + dp[v][1], notGiven = dp[v][0];
			int cur = ss - notGiven + given;
			if (cur == dp[u][b]) { choice = v; break; }
		}
	}

	for (auto &v : adj[u]) {
		if (v == p) { continue; }
		if (v == choice) { res.emplace_back(choice); back(v, 1, u); }
		else { back(v, 0, u); }
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("grant.in");
	ofstream ofs("grant.out");

	for (int i = 0; i < 500002; i++) { dp[i][0] = dp[i][1] = -1; }

	int n; ifs >> n; adj.resize(n);
	for (int i = 1; i < n; i++) {
		int p; ifs >> p; p--;
		adj[i].emplace_back(p);
		adj[p].emplace_back(i);
	}

	findMax(0, 0, -1); back(0, 0, -1);

	ofs << dp[0][0] * 1000 << '\n';
	sort(res.begin(), res.end());
	for (auto &x : res) { ofs << x + 1 << ' '; }
	ofs << '\n';
}