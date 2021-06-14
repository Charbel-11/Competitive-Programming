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
		vector<string> nums(n); for (auto& x : nums) { cin >> x; }

		int ans = 0;
		for (int i = 1; i < n; i++) {
			if (nums[i].size() > nums[i-1].size()) { continue; }

			int j = 0;
			for (; j < nums[i].size(); j++) {
				if (nums[i][j] != nums[i - 1][j]) { break; }
			}
			if (j == nums[i].size()) {
				bool fixed = false;		
				ans += nums[i - 1].size() - nums[i].size();
				for (int k = nums[i - 1].size() - 1; k >= j; k--) {
					if (nums[i - 1][k] < '9') {
						nums[i] = nums[i - 1]; nums[i][k] = nums[i][k] + 1; 
						for (int l = k + 1; l < nums[i].size(); l++) { nums[i][l] = '0'; }
						fixed = true; break;
					}
				}
				if (!fixed){
					ans++;
					while (nums[i].size() <= nums[i - 1].size()) { nums[i].push_back('0'); }
				}
			}
			else {
				if (nums[i][j] < nums[i - 1][j]) {
					while (nums[i].size() <= nums[i - 1].size()) { ans++; nums[i].push_back('0'); }
				}
				else {
					while (nums[i].size() < nums[i - 1].size()) { ans++; nums[i].push_back('0'); }
				}
			}
		}

//		for (auto& x : nums) { cout << x << " "; }
		
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}