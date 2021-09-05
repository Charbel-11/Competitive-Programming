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
		string s; int n; cin >> s >> n;

		multiset<int> candidate;
		vector<int> ans; int curPow = 1;
		for (int i = s.size() - 1; i >= 0; i--, curPow *= 10) {
			for (int j = 0; j < (s[i] - '0'); j++) {
				candidate.insert(curPow);
			}
		}

		if (candidate.size() >= n) {
			while (!candidate.empty()) { 
				ans.push_back(*candidate.begin());
				candidate.erase(candidate.begin());
			}
			while (ans.size() > n) { ans[0] += ans.back(); ans.pop_back(); }
		}
		else {
			int needed = n - candidate.size();

			while (needed > 0) {
				while (*candidate.begin() == 1) { 
					ans.push_back(1); 
					candidate.erase(candidate.begin()); 
				}

				int cur = *candidate.begin(); candidate.erase(candidate.begin());
				int otherNum = (cur / 10) * 9; cur /= 10;
				candidate.insert(cur);

				int jM = min(needed - 1, 9);
				for (int j = 0; j < jM; j++) { candidate.insert(cur); otherNum -= cur; needed--; }
				if (otherNum > 0) { candidate.insert(otherNum); needed--; }
			}

			while (!candidate.empty()) {
				ans.push_back(*candidate.begin());
				candidate.erase(candidate.begin());
			}
		}

		for (auto& x : ans) { cout << x << ' '; }
		cout << '\n';
	}
}