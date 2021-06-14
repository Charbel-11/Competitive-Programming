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
const ll mod = 998244353;

ll egcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
ll modinv(ll a, ll p = mod) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}

ll fact[3010];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < 3010; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

ll choose(ll n, ll k) {
	if (k > n) { return 0; }
	ll num = fact[n], denom = fact[k];
	denom *= fact[n - k]; denom %= mod;

	ll multInv = modinv(denom);
	num *= multInv; num %= mod;
	return num;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	string s, t; cin >> s >> t;
	int n = t.size(), m = s.size();
	fillFact();

	string sR = s; reverse(sR.begin(), sR.end());
	vector<vector<ll>> dp(m + 1, vector<ll>(n + 1, 0));
	for (int i = 0; i <= n; ++i) { dp[0][i] = 0; }
	for (int i = 0; i <= m; ++i) { dp[i][0] = 1; }
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (sR[i - 1] == t[j - 1]) { dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; }
			else { dp[i][j] = dp[i - 1][j]; }
		}
	}

	//dp[i][j] = #times t[0..j] appears in sR[0..i]

	ll ans = 0;
	for (int cut = 0; cut <= t.size(); cut++) {
		int j = 0;
		for (int i = 0; i < s.size(); i++) {
			if (j == t.size()) { break; }
			if (s[i] == t[j]) { j++; continue; }
		}
		if (j < t.size()) { continue; }

		if (cut == 0) {
			bool OK = true;
			for (int i = 0; i < s.size(); i++) {
				if (j == t.size()) { break; }
				if (s[i] != s[j]) { OK = false; break; }
			}
			ans += OK; continue;
		}
		ll cur = 0;
		int r = cut, l = cut - 1;
		cur += dp[s.size()][l+1];
//		cout << s.size() << " " << l+1 << " " <<dp[s.size()][l+1] << " ";
		cur *= choose(s.size(), cut);
		cout << cut << " " << cur << endl;
		ans += cur; ans %= mod;
	}
	cout << ans << endl;
}