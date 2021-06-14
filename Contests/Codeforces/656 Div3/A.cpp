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
		vector<int> nums(3); for (auto &x : nums) { cin >> x; }
		sort(nums.begin(), nums.end());
		if (nums[1] != nums[2]){ cout << "NO\n"; continue; }
		cout << "YES\n";
		cout << nums[0] << " " << nums[0] << " " << nums[1] << '\n';
	}
}