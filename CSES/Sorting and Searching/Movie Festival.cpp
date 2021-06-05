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

/*
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<int> comp;
	int n; cin >> n;
	vector<pair<int, int>> movies(n);
	for (auto &p : movies) { cin >> p.first >> p.second; comp.push_back(p.first); comp.push_back(p.second); }
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	for (int i = 0; i < n; i++) {
		movies[i].first = lower_bound(comp.begin(), comp.end(), movies[i].first) - comp.begin();
		movies[i].second = lower_bound(comp.begin(), comp.end(), movies[i].second) - comp.begin();
	}
	sort(movies.begin(), movies.end());

	vector<int> dp(2 * n + 1, 0); int j = 0;
	for (int i = 0; i <= 2*n; i++) {
		if (i) { dp[i] = max(dp[i], dp[i - 1]); }
		while (j < (int)movies.size() && movies[j].first == i) {
			int curS = movies[j].first, curE = movies[j].second;
			dp[curE] = max(dp[curE], dp[curS] + 1);
			j++;
		}
	}

	cout << dp.back() << '\n';
}
*/

int main() {
	int n; cin >> n;
	vector<pair<int, int>> v(n);
	for (auto &x : v) { cin >> x.second >> x.first; }
	sort(v.begin(), v.end()); 
	
	int cur = 0, res = 0;
	for (auto &x : v) {
		if (x.second < cur) { continue; }
		res++; cur = x.first;
	}
	cout << res << '\n';
}