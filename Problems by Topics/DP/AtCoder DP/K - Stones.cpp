#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n, k; cin >> n >> k;
	vector<int> A(n);
	for (auto &x : A) { cin >> x; }

	vector<bool> DP(k + 1, false);
	
	for (int i = 0; i <= k; i++) {
		for (int x : A) {
			if (i + x <= k && !DP[i])
				DP[i + x] = true;
		}
	}

	cout << (DP[k] ? "First" : "Second") << endl;
}