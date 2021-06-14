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

	int n, k; cin >> n >> k;
	vector<int> nums(n); for (auto& x : nums) { cin >> x; }
	while (k--) {
		int cur; cin >> cur;
		cout << upper_bound(nums.begin(), nums.end(), cur) - nums.begin() << '\n';
	}
}