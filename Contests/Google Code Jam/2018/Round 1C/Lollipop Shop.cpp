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
	int t; cin >> t;

	while (t--) {
		int n; cin >> n; if (n == -1) { return 0; }
		vector<int> freq(n, 0);	vector<bool> used(n, 0);
		vector<pair<double, int>> prob(n);

		for (int i = 1; i <= n; i++) {
			int D; cin >> D; if (D == -1) { return 0; }
			vector<int> curLike;
			while (D--) {
				int cur; cin >> cur; 
				freq[cur]++; curLike.push_back(cur);
			}

			prob.clear(); prob.resize(n, { 0,0 });
			for (int j = 0; j < curLike.size(); j++) {
				prob[curLike[j]].first = (double)freq[curLike[j]] / i;
				prob[curLike[j]].second = curLike[j];
			}
			sort(prob.begin(), prob.end());

			bool found = false;
			for (int j = 0; j < n; j++) {
				if (used[prob[j].second] || prob[j].first == 0) { continue; }
				cout << prob[j].second << endl; used[prob[j].second] = 1;
				found = true; break;
			}
			if (!found) { cout << -1 << endl; }
		}
	}
}