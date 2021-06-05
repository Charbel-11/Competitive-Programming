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
	vector<int> nums(n), res(n, -1);
	for (auto &x : nums) { cin >> x; }
	
	for (int i = 1; i < n; i++) {
		int j = i - 1;
		while (j >= 0 && nums[j] >= nums[i]) { j = res[j]; }
		res[i] = j;
	}

	for (auto &x : res) { cout << x + 1 << ' '; }
	cout << '\n';
}