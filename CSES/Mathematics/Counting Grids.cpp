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

ll powe(ll x, ll p) {
	x %= mod; p %= (mod - 1);
	ll ans = 1;
	for (; p > 0; p >>= 1, x = (x * x) % mod) {
		if (p & 1) { ans *= x; ans %= mod; }
	}
	return ans;
}
ll modinv(ll n) { return powe(n, mod - 2); }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n; cin >> n;
	ll p1, p2;
	if (n % 2) { 
		p1 = (n * n + 3) / 4;
		p2 = (n * n + 1) / 2;
	}
	else { 
		p1 = n * n / 4;
		p2 = (n * n) / 2;
	}

	ll c0 = powe(2, n * n);
	ll c1 = powe(2, p1);
	ll c2 = powe(2, p2);
	ll c3 = c1;
	ll C = ((c0 + c1) % mod) + ((c2 + c3) % mod); C %= mod;

	ll ans = modinv(4) * C; ans %= mod;
	cout << ans << '\n';
}
