#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

ll euler_phi(ll n) {
	ll res = n;
	for (ll i = 2; i * i <= n; i++)
		if (n % i == 0) {
			while (n % i == 0) { n /= i; }
			res -= res / i;
		}
	if (n > 1) { res -= res / n; }
	return res;
}

bool isPrime(ll n) {
	if (n < 2) { return false; }
	if (n < 4) { return true; }
	if (n % 6 != 1 && n % 6 != 5) { return false; }

	for (ll i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

void fact(ll n, vector<pair<ll, ll>> &f) {
	if (isPrime(n)) { f.push_back({ n, 1 }); return; }
	for (ll i = 2; n > 1; i++) {
		if (n % i == 0) {
			ll x = 0;
			while (n % i == 0) { x++; n /= i; }
			f.push_back({ i, x });
			if (n == 1) { break; }
			if (isPrime(n)) { f.push_back({ n, 1 }); break; }
		}
	}
}

ll power(ll x, ll n, ll mod) {
	if (n == 0) { return 1; }
	ll res = power(x, n / 2, mod);
	res *= res; res %= mod;
	if (n % 2) { return (res * x) % mod; }
	return res;
}

int a[4] = { 1, 2, 9, 262144 };

ll exponial(ll n, ll mod) {
	if (n < 5) { return a[n - 1] % mod; }
	if (n % mod == 0) { return 0; }
	vector<pair<ll, ll>> f; fact(n, f);
	ll res = 1, next_mod = euler_phi(mod);
	ll next_exp = exponial(n - 1, next_mod);
	for (int i = 0; i < (int)f.size(); i++) {
		res *= power(f[i].first, f[i].second * ((next_exp % next_mod) + next_mod), mod);
		res %= mod;
	}
	return res;
}

int main() {
	ll n, m; cin >> n >> m;
	if (n < 5) { cout << a[n - 1] % m << endl; }
	else { cout << exponial(n, m) << endl; }
	cin.ignore(2); return 0;
}