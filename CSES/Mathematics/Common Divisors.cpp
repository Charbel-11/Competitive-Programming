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
	
	int maxV = *max_element(nums.begin(), nums.end());
	vector<int> occ(maxV + 1, 0);
	for (auto &x : nums) { occ[x]++; }

	int ans = 1;
	for (int i = maxV; i >= 1; i--) {
		if (occ[i] >= 2) { ans = i; break; }
		int cnt = 0;
		for (int j = i; j <= maxV; j += i) { cnt += occ[j]; }
		if (cnt >= 2) { ans = i; break; }
	}

	cout << ans << '\n';
}