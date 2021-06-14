#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t, n, q; cin >> t >> n >> q;
	for (int qq = 1; qq <= t; qq++) {
		vector<int> order(n);
		for (int i = 0; i < n; i++) { order[i] = i + 1; }
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		shuffle(order.begin(), order.end(), std::default_random_engine(seed));

		vector<int> ans = { order[0], order[1], order[2] };
		cout << order[0] << " " << order[1] << " " << order[2] << endl;
		int m; cin >> m;
		if (m == order[0]) { swap(ans[0], ans[1]); }
		else if (m == order[2]) { swap(ans[1], ans[2]); }

		for (int i = 3; i < n; i++) {
			int cur = order[i], l = 0, r = ans.size() - 1;
			while (l < r) {
				int mid = (l + r + 1) >> 1;
				cout << ans[l] << " " << cur << " " << ans[mid] << endl;
				cin >> m;

				if (m == ans[l]) { ans.insert(ans.begin() + l, cur); break; }
				if (m == cur) { 
					if (l == mid - 1) { ans.insert(ans.begin() + l + 1, cur); break; }
					l++; r = mid - 1;
					if (l == r) { r++; }
				}
				else { 
					if (mid == r) { ans.insert(ans.begin() + r + 1, cur); break; }
					l = mid + 1; 
					if (l == r) { l--; }
				}
			}
		}

		for (auto& x : ans) { cout << x << ' '; } cout << endl;
		int res; cin >> res;
		if (res == -1) { return 0; }
	}
}