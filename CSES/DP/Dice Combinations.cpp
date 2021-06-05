#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = (ll)1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> dp(n + 1, 0); 
	for (int i = 1; i <= min(n, 6); i++) { dp[i] = 1; }
	for (int i = 2; i <= n; i++) {
		for (int j = i - 1; j >= max(0, i - 6); j--) {
			dp[i] += dp[j];
			dp[i] %= mod;
		}
	}

	cout << dp[n] << '\n';
}