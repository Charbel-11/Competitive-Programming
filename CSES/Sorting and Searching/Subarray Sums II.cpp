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

	int n; ll x; cin >> n >> x;
	vector<int> nums(n);
	for (auto &y : nums) { cin >> y; }
	map<ll, int> freq; freq[0] = 1;

	ll res = 0, cur = 0;
	for (int i = 0; i < n; i++) {
		cur += nums[i];
		res += freq[cur - x];
		freq[cur]++;
	}

	cout << res << '\n';
}