#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n); for (auto& x : a) { cin >> x; }

		ll ans = 0;
		unordered_map<int, ll> m;
		for (int i = 0; i < n; i++) {
			ans += m[a[i]] * (n - i);
			m[a[i]] += i + 1;
		}

		cout << ans << '\n';
	}
}
