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
		int n, W; cin >> n >> W;
		multiset<int> w;
		for (int i = 0; i < n; i++) {
			int cur; cin >> cur; w.insert(cur);
		}

		int ans = 1, cur = 0;
		while (!w.empty()) {
			int available = W - cur;
			auto it = w.upper_bound(available);
			if (it == w.begin()) { ans++; cur = 0; }
			else { it--; cur += *it; w.erase(it); }
		}
		cout << ans << '\n';
	}
}
