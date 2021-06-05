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

	int n; cin >> n;
	vector<pair<pair<int, int>, int>> cust(n);
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		cust[i] = { {l,r},i };
	}
	sort(cust.begin(), cust.end());

	int res = 0; vector<int> ans(n);
	set<int> available;
	for (int i = 1; i <= n; i++) { available.insert(i); }

	multimap<int, int> active;
	for (int i = 0; i < n; i++) {
		int curS = cust[i].first.first, curE = cust[i].first.second;
		while (!active.empty() && (*active.begin()).first < curS) {
			int room = active.begin()->second;
			available.insert(room);
			active.erase(active.begin());
		}

		int curRoom = *available.begin();
		ans[cust[i].second] = curRoom;
		available.erase(available.begin());
		res = max(res, curRoom);
		active.insert({ curE, curRoom });
	}

	cout << res << '\n';
	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}