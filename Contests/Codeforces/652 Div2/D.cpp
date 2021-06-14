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

const ll mod = 1000 * 1000 * 1000 + 7;

// fast exponentiation modulo mod
ll powe(ll x, ll p) {
	if (p == 0) return 1;
	ll w = powe((x*x) % mod, p / 2);
	if (p & 1) w = (w*x) % mod;
	return w;
}

// modular inverse (mod must be prime)
ll modinv(ll i) { return powe(i, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	vector<ll> ans((int)2e6 + 10, 0), leaves((int)2e6 + 10, 0); 
	leaves[1] = leaves[2] = 1;

	for (int i = 3; i < (int)2e6 + 10; i++) {
		leaves[i] = leaves[i - 2] * 2 + leaves[i - 1];
		leaves[i] %= mod;
		ll diff = leaves[i] - leaves[i - 1]; diff += mod; diff %= mod;
		diff *= 4; diff %= mod; diff *= modinv(2); diff %= mod;
		ans[i] = diff;
		ans[i] += ans[i - 3]; ans[i] %= mod;
	}

	while (t--) {
		ll n; cin >> n;		
		cout << ans[n] << '\n';
	}
}