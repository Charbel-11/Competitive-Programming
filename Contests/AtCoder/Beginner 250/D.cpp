#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool isPrime[1000004];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<ll> prime;
	for (ll i = 2; i < 1000004; i++) { isPrime[i] = true; }
	for (ll i = 2; i < 1000004; i++) {
		if (!isPrime[i]) { continue; }
		prime.push_back(i);
		for (ll j = i * i; j < 1000004; j += i) { isPrime[j] = false; }
	}

	ll n; cin >> n; 
	ll ans = 0;
	for (auto& q : prime) {
		ll cur = q * q * q;
		if (cur > n) { break; }

		ll maxP = n / cur; maxP = min(maxP, q - 1);
		ans += (upper_bound(prime.begin(), prime.end(), maxP) - prime.begin());
	}

	cout << ans << '\n';
}
