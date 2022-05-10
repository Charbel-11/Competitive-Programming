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
		vector<pair<int, int>> col(n);
		for (int i = 0; i < n; i++) { cin >> col[i].first; col[i].first--; }
		for (int i = 0; i < n; i++) { cin >> col[i].second; col[i].second--; }
		sort(col.begin(), col.end());

		int maxTaken = 0;
		vector<bool> used(n, 0);
		for (int i = 0; i < n; i++) {
			if (used[i]) { continue; }

			int cur = i, curLen = 0; 
			while (!used[cur]) {
				curLen++; used[cur] = true;
				cur = col[cur].second;
			}

			maxTaken += curLen / 2;
		}

		ll ans = 0;
		for (int i = 1; i <= maxTaken; i++) { ans -= i; }
		for (int i = n; i > n - maxTaken; i--) { ans += i; }
		ans *= 2;
		cout << ans << '\n';
	}
}
