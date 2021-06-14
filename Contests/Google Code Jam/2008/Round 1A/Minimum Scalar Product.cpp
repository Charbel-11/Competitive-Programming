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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<ll> x1(n), x2(n);
		for (auto& x : x1) { cin >> x; }
		for (auto& x : x2) { cin >> x; }

		sort(x1.begin(), x1.end());
		sort(x2.rbegin(), x2.rend());

		ll ans = 0;
		for (int i = 0; i < n; i++) { ans += x1[i] * x2[i]; }

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}