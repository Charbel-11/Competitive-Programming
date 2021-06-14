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

// a*x - b*y = return value = GCD(a,b). x,y >= 0
ll egcd(ll a, ll b, ll &x, ll &y) { // MINUS B*Y
	if (b == 0) {
		x = 1; y = 0;
		return a;
	}

	ll d = egcd(b, a%b, y, x);
	y = a - x * (a / b) - y;
	x = b - x;
	return d;
}
// modular inverse; works for any mod p (coprime with a)
ll inverse(ll a, ll p = mod) {
	ll x, y;
	egcd(a%p + p, p, x, y);
	return x % p;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<ll> d(n); for (auto &x : d) { cin >> x; }
	vector<pair<ll, ll>> shields(m);
	for (auto &p : shields) { cin >> p.first >> p.second; }

	sort(d.begin(), d.end());

	vector<ll> dmg(n + 1, 0);
	for (int i = n - 1; i >= 0; i--) {
		dmg[i] = d[i] + dmg[i+1]; dmg[i] %= mod;
	}

	for (int i = 0; i < m; i++) {
		ll a = shields[i].first, b = shields[i].second;

		int idx = lower_bound(d.begin(), d.end(), b) - d.begin();
		int k = n - idx;
		if (k < a) { cout << 0 << '\n'; continue; }

		ll tmp = a * inverse(k); tmp = 1 - tmp; tmp %= mod;
		ll ans = dmg[n - k] * tmp; ans %= mod;
		
		ll weakDmg = dmg[0] - dmg[n - k];
		weakDmg *= (1 - a * inverse(k + 1)) % mod; weakDmg %= mod;
		ans += weakDmg; ans %= mod;

		if (ans < 0) { ans += mod; }
		cout << ans << '\n';
	}
}