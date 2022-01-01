// https://codeforces.com/contest/1316/problem/E

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int getNumBits(int x) {
	int ans = 0;
	while (x) { x &= (x - 1); ans++; }
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, p, k; cin >> n >> p >> k;
	vector<vector<ll>> s(n, vector<ll>(p + 1));
	for (int i = 0; i < n; i++) { cin >> s[i][0]; }
	for (int i = 0; i < n; i++)
		for (int j = 1; j <= p; j++)
			cin >> s[i][j];
	sort(s.rbegin(), s.rend());
	
	vector<ll> dp(1 << p, -1e9); dp[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int m = (1 << p) - 1; m >= 0; m--) {
			int audTaken = i - getNumBits(m);
			if (audTaken < k && dp[m] >= 0) { dp[m] += s[i][0]; }
			for (int k = 0; k < p; k++) {
				int curM = m ^ (1 << k);
				if (m < curM || dp[curM] < 0) { continue; }
				dp[m] = max(dp[m], dp[curM] + s[i][k + 1]);
			}
		}
	}

	cout << dp.back() << '\n';
}