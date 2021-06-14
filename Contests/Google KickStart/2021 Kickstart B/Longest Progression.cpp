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
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<int> nums(n); for (auto& x : nums) { cin >> x; }
		vector<int> diff(n - 1);
		for (int i = 1; i < n; i++) { diff[i - 1] = nums[i] - nums[i - 1]; }
		cout << "Case #" << qq << ": ";
		if (n == 2) { cout << 2 << '\n'; continue; }

		vector<int> prefEq(n - 1, 1), sufEq(n - 1, 1);
		for (int i = 1; i < n - 1; i++) {
			if (diff[i] == diff[i - 1]) { prefEq[i] = prefEq[i - 1] + 1; }
		}
		for (int i = n - 2; i >= 0; i--) {
			if (diff[i] == diff[i + 1]) { sufEq[i] = sufEq[i + 1] + 1; }
		}
		int ans = max(*max_element(prefEq.begin(), prefEq.end()), *max_element(sufEq.begin(), sufEq.end())) + 1;

		ans = max(ans, sufEq[1] + 2);
		for (int i = 1; i < n - 1; i++) {
			if (i > 1) {
				int delta = diff[i - 2] - diff[i - 1];
				int curAns = prefEq[i - 2] + 2;
				int newDifR = diff[i] - delta;
				if (newDifR == diff[i - 2]) { 
					curAns++;
					if (i + 1 < diff.size() && newDifR == diff[i + 1]) { curAns += sufEq[i + 1]; }
				}				
				ans = max(ans, curAns);
			}

			if (i < n - 2) {
				int delta = diff[i] - diff[i + 1];
				int curAns = sufEq[i + 1] + 2;
				int newDifL = diff[i - 1] + delta;
				if (newDifL == diff[i + 1]) {
					curAns++;
					if (i - 2 >= 0 && newDifL == diff[i - 2]) { curAns += prefEq[i - 2]; }
				}
				ans = max(ans, curAns);
			}
		}
		ans = max(ans, prefEq[n - 3] + 2);

		cout << ans << '\n';
	}
}
