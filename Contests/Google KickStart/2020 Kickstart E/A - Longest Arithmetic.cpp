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
		vector<int> a(n); for (auto &x : a) { cin >> x; }

		int ans = 2, l = 0;
		for (int i = 2; i < n; i++) {
			if (a[i] - a[i - 1] == a[i - 1] - a[i - 2]) { ans = max(ans, i - l + 1); }
			else { l = i - 1; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}