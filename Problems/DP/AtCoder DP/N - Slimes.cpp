#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
ll prefix[402];
ll cost[402][402];

ll sum(int l, int r) {
	return prefix[r] - (l > 0 ? prefix[l - 1] : 0);
}

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) { cost[i][j] = 1e15; }
		prefix[i] = nums[i] + (i ? prefix[i - 1] : 0);
		cost[i][i] = 0;
	}

	for (int l = n-1; l >= 0; l--)
		for (int r = l + 1; r < n; r++)
			for (int k = l; k < r; k++)
				cost[l][r] = min(cost[l][r], cost[l][k] + cost[k + 1][r] + sum(l, r));

	cout << cost[0][n - 1] << endl;
}