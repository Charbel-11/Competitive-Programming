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

	int n, k; cin >> n >> k;
	vector<pair<int, int>> movies(n);
	for (auto &p : movies) { cin >> p.first >> p.second; }
	sort(movies.begin(), movies.end());

	multiset<int> active;
	int res = n;
	for (int i = 0; i < n; i++) {
		int curS = movies[i].first, curE = movies[i].second;
		while (!active.empty() && *active.begin() <= curS) { active.erase(active.begin()); }
		active.insert(curE);
		if ((int)active.size() == k + 1) { active.erase(prev(active.end())); res--; }
	}

	cout << res << '\n';
}