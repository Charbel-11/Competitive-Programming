#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	int n, k; cin >> n >> k;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	ll pSum = 0, ways = 1;
	for (int i = 0; i < k; i++) { pSum += n - i; }
	ll smallest = n - (k - 1);

	bool first = true; int prevIdx = 0;
	for (int i = 0; i < n; i++) {
		if (nums[i] >= smallest) {
			if (first) { first = 0; prevIdx = i; continue; }

			ways *= (i - prevIdx); ways %= mod;
			prevIdx = i;
		}
	}

	cout << pSum << " " << ways << endl;
}