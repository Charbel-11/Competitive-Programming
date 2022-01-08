#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 998244353;

// fast exponentiation modulo mod
int powe(int x, int p) {
	int res = 1;
	for (; p; p >>= 1, x = ((ll)x * x) % mod)
		if (p & 1) { res = ((ll)res * x) % mod; }
	return res;
}
// modular inverse (mod must be prime)
int modinv(int i) { return powe(i, mod - 2); }

const int SZ = (int)2e5 + 1;
int fact[SZ];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < SZ; i++) {
		fact[i] = ((ll)fact[i - 1] * i) % mod;
	}
}

int choose(int n, int k) {
	if (k > n) { return 0; }
	int num = fact[n], denom = fact[k];
	denom = ((ll)denom * fact[n - k]) % mod;

	int multInv = modinv(denom);
	num = ((ll) num * multInv) % mod;
	return num;
}

int freq[26];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	fillFact();
	string s; cin >> s; int n = s.size();
	for (auto& c : s) { freq[c - 'a']++; }

	vector<vector<int>> dp(26, vector<int>(n + 1, 0));
	for (int i = 0; i <= freq[0]; i++) { dp[0][i] = 1; }

	int curMax = freq[0];
	for (int i = 1; i < 26; i++) {
		curMax += freq[i];
		for (int j = 0; j <= curMax; j++) {
			int limit = min(j, freq[i]);
			for (int k = 0; k <= limit; k++) {
				int curNum = j - k;
				dp[i][j] += ((ll)dp[i - 1][curNum] * choose(j, k)) % mod;
				dp[i][j] %= mod;
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += dp[25][i]; ans %= mod;
	}
	cout << ans << '\n';
}