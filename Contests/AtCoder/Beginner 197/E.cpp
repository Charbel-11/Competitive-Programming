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

	int n; cin >> n;
	vector<pair<ll, int>> balls(n); vector<int> comp;
	for (auto& b : balls) { cin >> b.first >> b.second; comp.push_back(b.second); }
	balls.push_back({ 0,0 }); balls.push_back({ 0, n + 1 });
	comp.push_back(0); comp.push_back(n + 1);
	
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());
	for (auto& b : balls) { b.second = lower_bound(comp.begin(), comp.end(), b.second) - comp.begin(); }

	int m = comp.size(); vector<ll> l(m, -1), r(m);
	sort(balls.begin(), balls.end());
	for (auto& b : balls) {
		if (l[b.second] == -1) { l[b.second] = b.first; }
		r[b.second] = b.first;
	}

	vector<vector<ll>> dp(m, vector<ll>(2));
	dp[0][0] = dp[0][1] = 0;

	for (int i = 1; i < m; i++) {
		dp[i][0] = min(abs(r[i] - l[i - 1]) + dp[i - 1][0], abs(r[i] - r[i - 1]) + dp[i - 1][1]) + abs(r[i] - l[i]);
		dp[i][1] = min(abs(l[i] - l[i - 1]) + dp[i - 1][0], abs(l[i] - r[i - 1]) + dp[i - 1][1]) + abs(r[i] - l[i]);
	}

	cout << dp[m - 1][0] << '\n';
}