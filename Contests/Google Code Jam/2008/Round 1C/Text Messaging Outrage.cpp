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
		int p, k, l; cin >> p >> k >> l;
		vector<int> freq(l); for (auto& x : freq) { cin >> x; }
		sort(freq.rbegin(), freq.rend());

		ll ans = 0, pos = 1, used = 0;
		for (int i = 0; i < l; i++) {
			if (used == k) { used = 0; pos++; }
			ans += freq[i] * pos; used++;
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}