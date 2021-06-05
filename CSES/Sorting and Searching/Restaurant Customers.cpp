#include <iostream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	int res = 0;
	vector<pair<int, int>> customers(n);
	for (auto &p : customers) { cin >> p.first >> p.second; }
	sort(customers.begin(), customers.end());

	multiset<int> active;
	for (int i = 0; i < n; i++) {
		int curS = customers[i].first, curE = customers[i].second;
		while (!active.empty() && *active.begin() <= curS) { active.erase(active.begin()); }
		active.insert(curE);
		res = max(res, (int)active.size());
	}

	cout << res << '\n';
}