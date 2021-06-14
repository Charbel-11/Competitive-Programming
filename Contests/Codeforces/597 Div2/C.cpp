#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long mod = 1e9 + 7;

int main() {
	string s; cin >> s;
	int n = s.size();

	for (int i = 0; i < n; i++) {
		if (s[i] == 'm' || s[i] == 'w') { cout << 0 << endl; return 0; }
	}

	vector<long long> dp(n + 1, 0);
	dp[n] = dp[n - 1] = 1ll;
	for (int i = n - 2; i >= 0; i--) {
		dp[i] += dp[i + 1]; dp[i] %= mod;
		if (s[i] == s[i + 1] && (s[i] == 'u' || s[i] == 'n')) { dp[i] += dp[i + 2]; dp[i] %= mod; }
	}

	cout << dp[0] << endl;
}