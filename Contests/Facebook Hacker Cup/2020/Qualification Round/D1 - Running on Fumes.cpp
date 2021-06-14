#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n, m; ifs >> n >> m;
		vector <ll> c(n); for (auto &x : c) { ifs >> x; }
		c.push_back(0);

		deque<ll> Q;
		vector<ll> dp(n + 1, (ll)1e17); dp[0] = 0;
		for (int i = 1; i <= m; i++) {
			dp[i] = 0;
			if (c[i] == 0) { continue; }
			while (!Q.empty() && Q.back() > c[i]) { Q.pop_back(); }
			Q.push_back(c[i]);
		}
		for (int i = m + 1; i < n; i++) {
			if (Q.empty()) { break; }
			dp[i] = Q.front();
			if (Q.front() == dp[i - m] + c[i - m]) { Q.pop_front(); }
			if (c[i] == 0) { continue; }
			ll cur = dp[i] + c[i];
			while (!Q.empty() && Q.back() > cur) { Q.pop_back(); }
			Q.push_back(cur);
		}

		ofs << "Case #" << qq << ": " << (dp[n-1] == (ll)1e17 ? -1 : dp[n-1]) << '\n';
	}
}