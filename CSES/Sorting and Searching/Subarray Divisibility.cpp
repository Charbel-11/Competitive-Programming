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

int freq[(int)2e5 + 5];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	freq[0] = 1;
	ll res = 0; int cur = 0;
	for (int i = 0; i < n; i++) {
		cur += nums[i]; cur %= n;
		cur += n; cur %= n;
		res += freq[cur];
		freq[cur]++;
	}

	cout << res << '\n';
}