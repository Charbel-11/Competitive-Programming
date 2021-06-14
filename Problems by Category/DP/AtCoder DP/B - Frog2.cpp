#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<int> h(n);
	for (auto &x : h) { cin >> x; }
	vector<int> DP(n, INT_MAX);
	DP[0] = 0;

	for (int i = 1; i < n; i++)
		for (int j = i - 1; j >= (max(0, i - k)); j--)
			DP[i] = min(DP[i], DP[j] + abs(h[i] - h[j]));

	cout << DP[n - 1] << endl;
}