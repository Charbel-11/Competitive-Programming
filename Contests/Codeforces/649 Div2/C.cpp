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

	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }
	if (nums[0] > 1) { cout << -1 << '\n'; return 0; }

	vector<int> ans(n, -1);
	set<int> available;
	for (int i = 0; i <= n; i++) { available.insert(i); }

	int curM = 0;
	vector<int> unused;
	for (int i = 0; i < n; i++) {
		if (nums[i] > curM) { 
			ans[i] = curM; curM = nums[i];
			available.erase(ans[i]);
			for (int kk = unused.size() - 1; kk >= 0; kk--) {
				int j = unused[kk], cur = *available.begin();
				if (cur < curM) { ans[j] = cur; available.erase(cur); unused.pop_back(); }
				else { break; }
			}
		}

		if (ans[i] == -1) { unused.push_back(i); }
	}

	for(auto i : unused){
		ans[i] = n + 2;
	}

	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}