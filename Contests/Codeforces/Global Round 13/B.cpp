#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		ll u, v; cin >> u >> v;
		vector<int> a(n); 
		for (auto& x : a) { cin >> x; }

		ll ans = min(u + v, v + v);
		for (int i = 1; i < n; i++) {
			if (abs(a[i] - a[i - 1]) > 1) { ans = 0; break; }
			if (abs(a[i] - a[i - 1]) == 1) {
				ans = min({ ans, u, v });
			}
		}
		cout << ans << '\n';
	}
}