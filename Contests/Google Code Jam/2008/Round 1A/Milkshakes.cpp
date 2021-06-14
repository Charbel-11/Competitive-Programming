#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n, m; cin >> n >> m;
		vector<int> ans(n, 0);
		vector<map<int, int>> cust(m);
		vector<vector<int>> milkshakes0(n);
		for (int i = 0; i < m; i++) {
			int tNum; cin >> tNum;
			while (tNum--) {
				int x, y; cin >> x >> y; x--;
				cust[i].insert({ x,y });
				if (!y) { milkshakes0[x].push_back(i); }
			}
		}

		stack<int> S;
		for (auto& c : cust) {
			if (c.size() == 1 && c.begin()->second == 1) {
				S.push(c.begin()->first);
			}
		}

		bool OK = true;
		while (!S.empty()) {
			int cur = S.top(); S.pop();
			if (ans[cur] == 1) { continue; }
			ans[cur] = 1;
			for (auto& x : milkshakes0[cur]) {
				cust[x].erase(cur);
				if (cust[x].size() == 1 && cust[x].begin()->second == 1)
					S.push(cust[x].begin()->first);
				else if (cust[x].size() == 0) { OK = false; break; }
			}
		}

		cout << "Case #" << qq << ": ";
		if (!OK) { cout << "IMPOSSIBLE" << '\n'; continue; }
		for (auto& x : ans) { cout << x << ' '; } cout << '\n';
	}
}