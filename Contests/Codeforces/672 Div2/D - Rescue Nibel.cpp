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

ll fact[(int)3e5 + 5];
void fillFact() {
	fact[0] = 1;
	for (int i = 1; i < (int)3e5 + 1; i++) {
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
}

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
	return w;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

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

	fillFact();
	ll n, k; cin >> n >> k;
	vector<pair<int, int>> lights(n);
	for (auto &p : lights) { cin >> p.first >> p.second; }
	sort(lights.begin(), lights.end());
	multiset<int> curOn;
	
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		while (!curOn.empty() && *curOn.begin() < lights[i].first) {
			curOn.erase(curOn.begin());
		}

		if (curOn.size() >= k - 1) { ans += choose(curOn.size(), k - 1); ans %= mod; }
		curOn.insert(lights[i].second);
	}

	cout << ans << '\n';
}