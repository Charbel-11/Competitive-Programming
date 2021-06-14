#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> h(n);
	for (auto &x : h) { cin >> x; }
	vector<int> DP(n, 0);
	DP[1] = abs(h[0] - h[1]);

	for (int i = 2; i < n; i++) {
		DP[i] = min(DP[i - 1] + abs(h[i] - h[i - 1]), DP[i - 2] + abs(h[i] - h[i - 2]));
	}

	cout << DP[n - 1] << endl;
}