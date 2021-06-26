#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#define deb(x) cout << #x << " " << x 
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<ll> d(n); for (auto& x : d) { cin >> x; }
		sort(d.begin(), d.end());

		ll ans = 0, pref = 0;
		for (int i = 2; i < n; i++) {
			pref += d[i - 2]; 
			ans -= (d[i] * (i - 1) - pref);
		}

		cout << ans << '\n';
	}
}