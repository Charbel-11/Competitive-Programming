#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	ll posI = 0, negI = 0;
	vector<bool> sign(n);
	sign[0] = nums[0] > 0;
	if (sign[0]) { posI++; }
	else { negI++; }
	for (int i = 1; i < n; i++) {
		if (nums[i] > 0) {
			sign[i] = sign[i - 1];
		}
		else {
			sign[i] = !sign[i - 1];
		}

		if (sign[i]) { posI++; }
		else { negI++; }
	}

	ll neg = negI, pos = posI;
	for (int i = 1; i < n; i++) {
		if (nums[i-1] > 0) {
			posI--;
		}
		else {
			negI--;
			swap(negI, posI);
		}
		neg += negI;
		pos += posI;
	}

	cout << neg << " " << pos << endl;
}