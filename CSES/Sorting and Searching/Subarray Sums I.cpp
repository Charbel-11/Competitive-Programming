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

	int n, x; cin >> n >> x;
	vector<int> nums(n); 
	for (auto &x : nums) { cin >> x; }

	int l = 0, cur = 0, res = 0;
	for (int r = 0; r < n; r++) {
		cur += nums[r];
		while (cur > x) { cur -= nums[l]; l++; }
		if (cur == x) { res++; }
	}

	cout << res << '\n';
}