#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

ll gcd(ll a, ll b) { return (b ? gcd(b, a % b) : a); }
ll pow(ll x, ll p) {
	ll ans = 1;
	for (; p > 0; p >>= 1, x = (x * x) % mod) {
		if (p & 1) { ans *= x; ans %= mod; }
	}
	return ans;
}
ll modinv(ll n) { return pow(n, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n, m; cin >> n >> m;
	ll ans = 0;
	for (int k = 0; k < n; k++) {
		ll cur = modinv(n);
		cur *= pow(m, gcd(k, n)); cur %= mod;
		ans += cur; ans %= mod;
	}
	cout << ans << '\n';
}
