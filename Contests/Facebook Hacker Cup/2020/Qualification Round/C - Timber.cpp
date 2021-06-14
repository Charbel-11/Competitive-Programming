#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("input.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;

	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		vector<pair<int, int>> trees(n);
		vector<int> comp;
		for (int i = 0; i < n; i++) {
			int p, h; ifs >> p >> h;
			trees[i] = { p,h };
			comp.push_back(p);
			comp.push_back(p - h);
			comp.push_back(p + h);
		}
		sort(comp.begin(), comp.end());
		comp.erase(unique(comp.begin(), comp.end()), comp.end());
		sort(trees.begin(), trees.end());

		vector<ll> dp((int)comp.size(), 0);
		for (int i = 0; i < n; i++) {
			int p = trees[i].first, h = trees[i].second;	//not compressed
			int l = lower_bound(comp.begin(), comp.end(), p - h) - comp.begin();
			int cur = lower_bound(comp.begin(), comp.end(), p) - comp.begin();
			int r = lower_bound(comp.begin(), comp.end(), p + h) - comp.begin();
			
			dp[r] = max(dp[r], dp[cur] + (ll)h);
			dp[cur] = max(dp[cur], dp[l] + (ll)h);
		}

		ll ans = *max_element(dp.begin(), dp.end());
		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}