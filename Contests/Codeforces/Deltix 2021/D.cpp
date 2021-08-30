#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int findOr (int i, int j) {
	cout << "or " << i + 1 << " " << j + 1 << endl;
	int ans; cin >> ans;
	return ans;
}

int findAnd(int i, int j) {
	cout << "and " << i + 1 << " " << j + 1 << endl;
	int ans; cin >> ans;
	return ans;
}

void output(int ans) {
	cout << "finish " << ans << endl;
	int res; cin >> res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> nums(n, 0);

	int andAB = findAnd(0, 1);
	int andAC = findAnd(0, 2);
	int andBC = findAnd(1, 2);
	int orAB = findOr(0, 1);
	int orAC = findOr(0, 2);
	int orBC = findOr(1, 2);

	int xorAB = andAB ^ orAB;
	int xorAC = andAC ^ orAC;
	int xorBC = andBC ^ orBC;

	nums[0] = andAB | andAC;
	nums[1] = andAB | andBC;
	nums[2] = andAC | andBC;

	for (int i = 0; i < 31; i++) {
		if ((xorAB >> i) & 1) {
			if (((nums[0] >> i) & 1) || ((nums[1] >> i) & 1)) {
				//skip
			}
			else {
				if ((xorAC >> i) & 1) { nums[0] |= (1 << i); }
				else { nums[1] |= (1 << i); }
			}
		}

		if ((xorAC >> i) & 1) {
			if (((nums[0] >> i) & 1) || ((nums[2] >> i) & 1)) {
				//skip
			}
			else {
				if ((xorAB >> i) & 1) { nums[0] |= (1 << i); }
				else { nums[2] |= (1 << i); }
			}
		}

		if ((xorBC >> i) & 1) {
			if (((nums[1] >> i) & 1) || ((nums[2] >> i) & 1)) {
				//skip
			}
			else {
				if ((xorAB >> i) & 1) { nums[1] |= (1 << i); }
				else { nums[2] |= (1 << i); }
			}
		}
	}

	for (int i = 3; i < n; i++) {
		int curAnd = findAnd(0, i);
		int curOr = findOr(0, i);
		int curXor = curAnd ^ curOr;

		int remOnes = (nums[0] & curXor) ^ curXor;

		nums[i] = curAnd | remOnes;
	}

	sort(nums.begin(), nums.end());
	output(nums[k - 1]);
}