#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const long long mod = 1e9 + 7;

map<string, int> nameToCol = { {"white", 0}, {"yellow", 1}, {"green", 2}, {"blue", 3}, {"red", 4}, {"orange", 5} };

ll powe(ll n, ll p) {
	ll ans = 1;
	while (p) {
		if (p & 1) { ans *= n; ans %= mod; }
		n *= n; n %= mod; p /= 2;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k, n; cin >> k >> n;
	map<ll, int> color;
	vector<ll> fixed;

	for (int i = 0; i < n; i++) {
		ll v; cin >> v; fixed.push_back(v);
		string curC; cin >> curC;
		color[v] = nameToCol[curC];
	}

	vector<vector<bool>> bad(6, vector<bool>(6, false));
	for (int i = 0; i < 6; i++) { bad[i][i] = true; }
	bad[0][1] = bad[1][0] = bad[2][3] = bad[3][2] = bad[4][5] = bad[5][4] = true;

	vector<ll> markedNodes;
	for (auto x : fixed) {
		markedNodes.push_back(x); x /= 2;
		while (x) {
			markedNodes.push_back(x); x /= 2;
		}
	}
	sort(markedNodes.begin(), markedNodes.end());
	markedNodes.erase(unique(markedNodes.begin(), markedNodes.end()), markedNodes.end());
	
	ll freeNodes = 1;
	for (int i = 0; i < k; i++) {
		freeNodes *= 2; freeNodes %= (mod - 1);
	}
	freeNodes--; freeNodes -= markedNodes.size();
	freeNodes %= (mod - 1);
	if (freeNodes < 0) { freeNodes += (mod - 1); }

	map<pair<ll, int>, ll> dp;
	for (int i = markedNodes.size() - 1; i >= 0; i--) {
		ll cur = markedNodes[i];
		ll leftC = cur * 2;
		ll rightC = leftC + 1;

		for (int j = 0; j < 6; j++) {
			if (color.count(cur) && color[cur] != j) { dp[{cur, j}] = 0; continue; }

			ll leftVal = 0, rightVal = 0;
			if (!dp.count({ leftC, 0 })) { leftVal = 1; }
			if (!dp.count({ rightC, 0 })) { rightVal = 1; }

			for (int k = 0; k < 6; k++) {
				if (bad[j][k]) { continue; }
				if (dp.count({ leftC, k })) { leftVal += dp[{leftC, k}]; leftVal %= mod; }
				if (dp.count({ rightC, k })) { rightVal += dp[{rightC, k}]; rightVal %= mod; }
			}

			ll total = leftVal * rightVal; total %= mod;
			dp[{cur, j}] = total;
		}
	}

	ll ans = powe(4, freeNodes), markedNum = 0;
	for (int j = 0; j < 6; j++) { markedNum += dp[{1, j}]; markedNum %= mod; }
	ans *= markedNum; ans %= mod;

	cout << ans << '\n';
}