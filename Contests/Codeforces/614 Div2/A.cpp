#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;
	
	while (t--) {
		ll n, s, k; cin >> n >> s >> k;

		vector<int> closed(k);
		for (auto &x : closed) { cin >> x; }

		sort(closed.begin(), closed.end());

		ll closest = s;
		if (!binary_search(closed.begin(), closed.end(), s)) { cout << 0 << endl; continue; }
		ll count = 1; bool found = false;
		ll ans = INT_MAX;
		for (int i = s + 1; i <= min(n, s + 1000ll); i++) {
			if (!binary_search(closed.begin(), closed.end(), i)) {
				ans = min(ans, count); break;
			}
			count++;
		}
		count = 1;
		for (int i = s - 1; i >= max(1ll, s - 1000); i--) {
			if (!binary_search(closed.begin(), closed.end(), i)) {
				ans = min(ans, count); break;
			}
			count++;
		}

		cout << ans << endl;
	}
}