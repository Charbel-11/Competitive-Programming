#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;

ll divisors(ll num) {
	if (num == 1) { return 1; }

	ll limit = sqrt(num);
	ll res = 0;

	for (ll i = 1; i <= limit; i++) {
		if (num%i == 0) {
			res += 2;
		}
	}
	if (limit*limit == num) { res--; }

	return res;
}

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
	int n;
	cin >> n;

	vector<ll> nums(n);
	for (int i = 0; i < n; i++) { cin >> nums[i]; }

	ll g = nums[0];
	for (int i = 1; i < n; i++) {
		g = gcd(g, nums[i]);
	}

	cout << divisors(g) << endl;
}