#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;
typedef long long ll;

int n, x;

void generate(unordered_map<int, int> &res, vector<int> &v, const int &l, const int &r) {
	if (l > r) { return; }
	int n = r - l + 1;
	for (int i = 1; i < (1 << n); i++) {
		int cur = 0;
		for (int j = 0; j < n; j++) {
			if ((1 << j) & i) cur += v[l + j];
			if (cur > x) { break; }
		}
		if (cur <= x) { res[cur]++; }
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> x;
	vector<int> nums(n); for (auto &x : nums) { cin >> x; }
	sort(nums.begin(), nums.end());	//Makes freq2 a smaller map
	unordered_map<int, int> freq1, freq2;

	int sep = n / 2;
	generate(freq1, nums, 0, sep - 1);
	generate(freq2, nums, sep, n - 1);

	ll ans = freq1[x] + freq2[x];
	for (auto it = freq2.begin(); it != freq2.end(); it++) {
		ans += (ll)freq2[it->first] * freq1[x - it->first];
	}

	cout << ans << '\n';
}