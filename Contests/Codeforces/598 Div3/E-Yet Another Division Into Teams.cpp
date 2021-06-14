#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;

	vector<pair<long long, int>> skills(n);
	for (int i = 0; i < n; i++) {
		long long s; cin >> s;
		skills[i] = { s, i };
	}
	sort(skills.begin(), skills.end());

	vector<long long> dp(n, INT_MAX); vector<int> teamSize(n, 0);

	dp[n - 3] = skills[n - 1].first - skills[n - 3].first; teamSize[n - 3] = 3;
	if (n - 4 >= 0) { dp[n - 4] = skills[n - 1].first - skills[n - 4].first; teamSize[n - 4] = 4; }
	if (n - 5 >= 0) { dp[n - 5] = skills[n - 1].first - skills[n - 5].first; teamSize[n - 5] = 5; }

	for (int i = n - 6; i >= 0; i--) {
		dp[i] = skills[i + 2].first - skills[i].first + dp[i + 3];
		teamSize[i] = 3;
		
		if (skills[i + 3].first - skills[i].first + dp[i + 4] < dp[i]) {
			dp[i] = skills[i + 3].first - skills[i].first + dp[i + 4];
			teamSize[i] = 4;
		}

		if (skills[i + 4].first - skills[i].first + dp[i + 5] < dp[i]) {
			dp[i] = skills[i + 4].first - skills[i].first + dp[i + 5];
			teamSize[i] = 5;
		}
	}

	vector<int> res(n); int teamCount = 1, i = 0;
	while(i < n){
		int tempI = i;
		while (teamSize[tempI]--) {
			res[skills[i].second] = teamCount; i++;
		}
		teamCount++;
	}

	cout << dp[0] << " " << teamCount - 1 << endl;
	for (auto &x : res) { cout << x << " "; } cout << endl;
}