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
	vector<vector<ll>> a(n, vector<ll>(n));
	for (auto& v : a) for (auto& x : v) cin >> x;

	vector<ll> score((1 << n), 0);
	for (int i = 1; i < (1 << n); i++) {
		for (int j = 0; j < n; j++) {
			if (!((1 << j) & i)) { continue; }
			score[i] = score[i ^ (1 << j)];
			for (int k = j + 1; k < n; k++) {
				if (!((1 << k) & i)) { continue; }
				score[i] += a[j][k];
			}
			break;
		}
	}

	vector<ll> dp((1 << n), 0);
	for (int i = 1; i < (1 << n); i++) {
		dp[i] = score[i];
		for (int j = i; j; j = (j - 1) & i) {
			dp[i] = max(dp[i], dp[j] + score[j ^ i]);
		}
	}

	cout << dp[(1 << n) - 1] << '\n';
}