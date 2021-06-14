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
	vector<int> nums(n); for (auto& x : nums) { cin >> x; }
	sort(nums.begin(), nums.end());
	int k; cin >> k;
	while (k--) {
		int l, r; cin >> l >> r;
		int idxL = lower_bound(nums.begin(), nums.end(), l) - nums.begin();
		int idxR = upper_bound(nums.begin(), nums.end(), r) - nums.begin() - 1;
		cout << (idxR - idxL + 1) << ' ';
	}
}