#include <iostream>
#include <string>
#include <map>
#include <set>
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
		string text; cin >> text;
		int n = text.size();

		int numS; cin >> numS;
		vector<string> vS(numS); for (auto& x : vS) { cin >> x; }

		vector<int> dp(n, 1e7);
		vector<pair<int, int>> choice(n, { -1,-1 });
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < numS; k++) {
				int wordS = vS[k].size();
				if (wordS > j + 1) { continue; }

				bool OK = true;
				for (int l = 0; l < wordS; l++) {
					if (text[j - l] != vS[k][wordS - 1 - l]) { OK = false; break; }
				}
				if (!OK) { continue; }

				if (wordS == j + 1) { dp[j] = 1; choice[j] = { k, wordS }; }
				else {
					int bestDP = dp[j - wordS], bestSize = wordS;
					for (int l = 1; l < wordS; l++) {
						if (dp[j - l] < bestDP) {
							bestDP = dp[j - l];
							bestSize = l;
						}
					}
					if (dp[j] > bestDP + 1) {
						dp[j] = bestDP + 1;
						choice[j] = { k, bestSize };
					}
				}
			}
		}

		if (dp[n - 1] == 1e7) { cout << -1 << '\n'; }
		else {
			cout << dp[n - 1] << '\n';

			int idx = n - 1;
			while (idx >= 0) {
				int i = choice[idx].first, l = choice[idx].second;
				int curLen = vS[i].size();
				cout << i + 1 << ' ' << idx - curLen + 2 << '\n';
				idx -= l;
			}
		}
	}
}
