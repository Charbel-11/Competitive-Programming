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

struct project {
	int s, e; ll r;
	project(int _s, int _e, ll _r) :s(_s), e(_e), r(_r) {}

	bool operator <(project &rhs) {
		if (s == rhs.s) { return e < rhs.e; }
		return s < rhs.s;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> comp;
	vector<project> projects;
	for (int i = 0; i < n; i++) {
		int s, e; ll r; cin >> s >> e >> r;
		comp.push_back(s); comp.push_back(e);
		projects.push_back(project(s, e, r));
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	int maxS = 0;
	for (int i = 0; i < n; i++) {
		projects[i].s = lower_bound(comp.begin(), comp.end(), projects[i].s) - comp.begin() + 1;
		projects[i].e = lower_bound(comp.begin(), comp.end(), projects[i].e) - comp.begin() + 1;
		maxS = max(maxS, projects[i].e);
	}
	sort(projects.begin(), projects.end());

	vector<ll> dp(maxS + 1, 0); int j = 0;
	for (int i = 1; i < maxS + 1; i++) {
		dp[i] = max(dp[i], dp[i - 1]);
		while (j < n && projects[j].s == i) {
			int e = projects[j].e;
			dp[e] = max(dp[e], dp[i - 1] + projects[j].r);
			j++;
		}
	}

	cout << dp.back() << '\n';
}