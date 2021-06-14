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
		int n; cin >> n;
		vector<int> a(n);
		for (auto &x : a) { cin >> x; }
		sort(a.begin(), a.end());

		int ans = 1, i = 0;

		while (i<n) {
			while (i < n && ans >= a[i]) {
				ans++; i++;
			}
			int cur = ans;
			while (i < n && cur < a[i]) {
				cur++; i++;
			}
			if (i == n) { break; }
			ans = cur;
		}

		cout << ans << endl;
	}
}