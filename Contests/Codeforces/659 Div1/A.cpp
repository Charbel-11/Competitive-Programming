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

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string A, B; cin >> A >> B;

		vector<vector<int>> needed(20);

		for (int i = 0; i < n; i++) {
			if (A[i] == B[i]) { continue; }
			needed[A[i] - 'a'].push_back(B[i] - 'a');
		}

		bool OK = true; int ans = 0;
		for (int i = 0; i < 20; i++) {
			if (needed[i].empty()) { continue; }
			int target = *min_element(needed[i].begin(), needed[i].end());
			if (target < i) { OK = false; break; }
			ans++;
			for (int j = 0; j < needed[i].size(); j++) {
				if (needed[i][j] != target) { needed[target].push_back(needed[i][j]); }
			}
		}

		if (!OK) { cout << -1 << '\n'; }
		else { cout << ans << '\n'; }
	}
}