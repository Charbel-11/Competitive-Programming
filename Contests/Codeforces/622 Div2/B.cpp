#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n, x, y; cin >> n >> x >> y;

		int minCase = 0;
		int curRank = x + y;

		if (curRank < n) { minCase = 1; }
		else {
			int startPt = curRank - n;
			minCase = startPt + 1;
		}
		cout << min(minCase, n) << " ";

		int worstCase = 0;

		if (curRank > n) { worstCase = n; }
		else {
			worstCase = curRank - 1;
		}

		cout << worstCase << endl;
	}
}