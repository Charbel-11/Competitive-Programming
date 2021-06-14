#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
typedef long long ll;
const ll mod = 998244353;

ll power(ll x, ll p) {
	if (p == 0) { return 1ll; }
	x %= mod;
	ll temp = power(x, p / 2) % mod;
	temp *= temp; temp %= mod;
	if (p & 1) temp *= x; temp %= mod;
	return temp;
}

int main() {
	int n; cin >> n;

	for (int i = 1; i <= n; i++) {
		if (i == n) { cout << 10 << " "; continue; }

		ll k = n - i;
		ll res = k - 1; res *= 10; res %= mod;
		res *= 9 * 9; res %= mod;
		ll pp = power(10, k - 2);
		res *= pp; res %= mod;

		ll part2 = 20 * 9; ll pp2 = power(10, k - 1);
		part2 *= pp2; part2 %= mod;
		res += part2; res %= mod;

		cout << res << " ";
	}
	cout << endl;
}