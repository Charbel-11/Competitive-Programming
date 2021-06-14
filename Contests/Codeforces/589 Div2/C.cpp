#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

const long long mod = 1e9+7;

set<ll> primes;
void primeFactors(ll x) {
	long long num = 2;
	while (x != 1 && num*num <= x) {
		if (x % num == 0) {
			primes.insert(num);
			while(x%num == 0) x /= num;
		}

		num++;
	}
	if (x != 1) { primes.insert(x); }
}

ll multiply(ll a, ll b) {
	ll res = 0;
	a = a % mod; b = b % mod;
	while (b > 0) {
		if (b % 2) {
			res += a; res %= mod;
		}
		a *= 2; a %= mod;
		b /= 2;
	}
	return res;
}

ll power(const ll &x, const ll &p) {
	if (p == 0) { return 1ll; }

	if (p % 2 == 0) {
		ll temp = power(x, p / 2) % mod;

		return (multiply(temp,temp)) % mod;
	}
	else {
		ll temp = power(x, p / 2) % mod;

		ll temp2 = multiply(temp, temp) % mod;
		return (multiply(temp2,x)) % mod;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll x, n; cin >> x >> n;
	primeFactors(x);

	long long answ = 1;
	for (auto &el : primes) {
		ll x = el;
		while (x*el <= n && x*el >= x) { 
			x *= el;
		}
		ll used = (n - 1) / x;
		if (n == x) { used = 1; }

		ll temp = 1;
		temp = power(x, used);
		answ = multiply(answ, temp);

		x /= el;
		while (x != 1) {
			ll pow = n / x;
			pow -= used;
			used += pow;

			temp = power(x, pow);
			answ = multiply(answ, temp);

			x /= el;
		}
	}

	cout << answ << endl;
}