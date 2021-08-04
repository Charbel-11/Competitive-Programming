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
		int n; cin >> n;
		vector<string> words(n);
		for (auto& s : words) { cin >> s; }

		int ans = 0;
		for (int i = 0; i < 5; i++) {
			char curChar = 'a' + i;
			vector<int> diff;

			for (int j = 0; j < n; j++) {
				int cur = 0;
				for (auto& c : words[j]) {
					if (c == curChar) { cur++; }
					else { cur--; }
				}
				diff.push_back(cur);
			}

			sort(diff.rbegin(), diff.rend());
			int curAns = 0, curCnt = 0;
			
			for (int j = 0; j < n; j++) {
				curCnt += diff[j];
				if (curCnt > 0) { curAns++; }
				else { break; }
			}

			ans = max(ans, curAns);
		}

		cout << ans << '\n';
	}
}