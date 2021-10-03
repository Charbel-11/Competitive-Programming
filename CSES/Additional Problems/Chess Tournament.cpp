#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		if (x) { pq.push({ x,i + 1 }); }
	}

	bool OK = true;
	vector<pair<int, int>> ans;
	while (!pq.empty()) {
		auto maxP = pq.top(); pq.pop();
		int x = maxP.first, i = maxP.second;
		if (pq.size() < x) { OK = false; break; }

		vector<pair<int, int>> changes;
		for (int j = 0; j < x; j++) {
			auto curP = pq.top(); pq.pop();
			ans.push_back({ i, curP.second });
			
			if (curP.first > 1) { changes.push_back({ curP.first - 1, curP.second }); }
		}

		for (auto& p : changes) { pq.push(p); }
	}

	if (!OK) { cout << "IMPOSSIBLE\n"; }
	else {
		cout << ans.size() << '\n';
		for (auto& p : ans) { cout << p.first << " " << p.second << '\n'; }
	}
}