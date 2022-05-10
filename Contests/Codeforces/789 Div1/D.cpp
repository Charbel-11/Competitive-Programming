#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		vector<int> v(n); for (auto& x : v) { cin >> x; }
		
		ll ans = 1; bool OK = true;
		for (int i = n - k; i <= n - 1; i++) {
			if (v[i] != -1 && v[i] != 0) { OK = false; break; }
		}
		for (int i = 0; i < n - k; i++) {
			if (v[i] > i) { OK = false; break; }
		}
		if (!OK) { cout << 0 << '\n'; continue; }

		for (int i = 1; i <= k; i++) { ans *= i; ans %= mod; }
		for (int i = k; i < n; i++) {
			if (v[i - k] > 0) { continue; }
			else if (v[i - k] == 0) {
				ans *= (k + 1); ans %= mod;
			}
			else {
				ans *= (i + 1); ans %= mod;
			}
		}

		cout << ans << '\n';
	}
}
