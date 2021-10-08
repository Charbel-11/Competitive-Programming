#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const long long mod = 1e9 + 7;

ll powe(ll n, ll p) {
	ll ans = 1;
	while (p) {
		if (p & 1) { ans *= n; ans %= mod; }
		n *= n; n %= mod; p /= 2;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int k; cin >> k;

	ll ans = 6, numNodes = 2;
	for (int i = 1; i < k; i++) {
		ll cur = powe(4, numNodes);
		ans *= cur; ans %= mod;
		numNodes *= 2; numNodes %= (mod - 1);
	}

	cout << ans << '\n';
}