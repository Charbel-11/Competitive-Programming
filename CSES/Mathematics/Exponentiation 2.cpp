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
ll mod = 1e9 + 7;

ll exp(ll a, ll b) {
	a %= mod;
	if (b == 0) { return 1ll; }
	ll temp = exp(a, b / 2);
	temp *= temp; temp %= mod;
	if (b & 1) { temp *= a; }
	return temp % mod;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		ll a, b, c; cin >> a >> b >> c;
		mod--; ll p = exp(b, c);
		mod++; ll ans = exp(a, p);
		cout << ans << '\n';
	}
}