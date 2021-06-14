#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

ll k, n;
vector<ll> a;
bool check(ll ans) {
	ll needed = ans * k;
	ll cur = 0;
	for (int i = 0; i < n; i++) {
		cur += min(ans, a[i]);
	}
	return cur >= needed;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cin >> k >> n;
	a.resize(n); for (auto& x : a) { cin >> x; }

	ll l = 0, r = 1e15;
	while (l < r) {
		ll mid = (l + r + 1) >> 1ll;
		if (check(mid)) { l = mid; }
		else { r = mid - 1; }
	}

	cout << l << '\n';
}