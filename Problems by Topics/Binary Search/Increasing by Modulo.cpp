//https://codeforces.com/problemset/problem/1168/A

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nums;
int m;

int bSearch(int a, int b) {
	if (a == b) { return a; }

	int mid = (a + b) / 2;

	int curNum = 0;
	int i = 0;

	while (i < nums.size()) {
		if (curNum < nums[i]) {
			if (m - (nums[i] - curNum) > mid) {
				curNum = nums[i];
			}
		}

		else if (curNum > nums[i]) {
			if (curNum - nums[i] > mid) {
				return bSearch(mid + 1, b);
			}
		}

		i++;
	}

	return bSearch(a, mid);
}

int main() {
	int n; cin >> n >> m;

	for (int i = 0; i < n; i++) {
		int temp; cin >> temp;
		nums.push_back(temp);
	}

	cout << bSearch(0, m) << endl;
}