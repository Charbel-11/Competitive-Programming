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

	while (t--) {
		ll m, n, k; cin >> m >> n >> k;
		ll ans = 0;
		vector<ll> wired(m);
		for (int i = 0; i < m; i++) { cin >> wired[i]; }

		sort(wired.begin(), wired.end());
		for (int i = 0; i < k; i++) {
			ans += n - wired[i];
		}
		for (int i = k; i < m; i++) {
			ans += wired[i];
		}
		
		cout << ans << '\n';
	}
}