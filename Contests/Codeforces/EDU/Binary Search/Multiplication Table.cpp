#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n; ll k;
ll smaller(ll num) {
	ll ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += min((ll)n, (num / i));
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	ll l = 0, r = 1e10;
	while (l < r) {
		ll mid = (l + r) / 2;
		if (smaller(mid) >= k) { r = mid; }
		else { l = mid + 1; }
	}
	cout << l << '\n';
}