#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
vector<vector<int>> nums;
int n, m;
int a1, a2;

bool check(int min) {
	vector<int> occ((1<<m), 0);
	vector<int> arrays;

	for (int i = 0; i < n; i++) {
		int cur = 0;
		for (int j = 0; j < m; j++) {
			if (nums[i][j] >= min)
				cur |= 1 << j;
		}
		arrays.push_back(cur);
		occ[cur]++;
	}

	int num1 = -1, num2 = -1;
	bool found = false;
	for (int i = 0; i < n; i++) {
		for (int target = 0; target < (1 << m); target++) {
			if ((target | arrays[i]) == ((1 << m) - 1)) {
				if (occ[target]) { num1 = arrays[i]; num2 = target; found = true; break; }
			}
		}
		if (found) break;
	}

	if (num1 == -1 && num2 == -1) { return false; }

	for (int i = 0; i < n; i++) {
		if (arrays[i] == num1) { a1 = i + 1; }
		if (arrays[i] == num2) { a2 = i + 1; }
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	nums.resize(n); for (auto &x : nums) { x.resize(m); }

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> nums[i][j];

	int l = 0, r = 1e9;

	while (l < r) {
		int mid = (l + r + 1) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	check(l);		//Needed if the minimum is 0 to update a1 and a2

	cout << a1 << " " << a2 << endl;
}