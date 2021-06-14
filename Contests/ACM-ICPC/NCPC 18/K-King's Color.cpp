#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
const ll mod = 1000000007;

ll comb[2501][2501];

void fillComb() {
	int limit = 2501;
	for (int i = 0; i < limit; i++) { comb[i][i] = 1; comb[i][0] = 1; }

	for (int i = 1; i < limit; i++)
		for (int j = 1; j < i; j++)
			comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
}

ll power(ll x, ll p) {
	if (p == 0) { return 1ll; }
	x %= mod;
	ll temp = power(x, p / 2) % mod;
	temp *= temp; temp %= mod;
	if (p & 1) temp *= x; temp %= mod;
	return temp;
}

int main() {
	ll n, k;
	cin >> n >> k;
	vector<int> v(n-1);
	for (auto &x : v) { cin >> x; }

	fillComb();

	ll ans = 0; 
	for (int i = 0; i < k; i++) {
		ll cur = (i % 2 == 0 ? 1 : -1) * comb[k][i] * (k - i); cur %= mod;
		cur *= power(k - i - 1, n - 1); cur %= mod;
		ans += cur;
		while (ans < 0) { ans += mod; }
	}

	cout << ans << endl;
}