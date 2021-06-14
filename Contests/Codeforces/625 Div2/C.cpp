#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) { nums[i] = s[i] - 'a'; }
	
	int ans = 0;

	for (int k = 25; k >= 0; k--) {
L:		for (int i = 0; i < nums.size(); i++) {
			if (nums[i] == k) {
				if (i > 0 && nums[i - 1] == k - 1) { ans++; nums.erase(nums.begin() + i); goto L; }
				if (i < nums.size() - 1 && nums[i + 1] == k - 1) { ans++; nums.erase(nums.begin() + i); goto L; }
			}
		}
	}

	cout << ans << endl;
}