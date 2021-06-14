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
		int n, m, x; cin >> n >> m >> x;
		vector<int> h(n); for (auto& xx : h) { cin >> xx; }
		vector<int> ans(n, -1);

		multimap<int, int> curH; for (int i = 0; i < m; i++) { curH.insert({ 0, i }); }
		for (int i = 0; i < n; i++) {
			int idx = curH.begin()->second;
			ans[i] = idx;
			int newH = curH.begin()->first + h[i];
			curH.erase(curH.begin());
			curH.insert({ newH, idx });
		}

		cout << "YES" << '\n';
		for (auto& x : ans) { cout << x + 1 << " "; }
		cout << '\n';
	}
}
