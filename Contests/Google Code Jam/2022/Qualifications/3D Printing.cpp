#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		vector<int> minInk(4, 1e7);

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				int cur; cin >> cur;
				minInk[j] = min(minInk[j], cur);
			}
		}

		int totalAvailable = 0, goal = 1000 * 1000;
		for (auto& x : minInk) { totalAvailable += x; }

		cout << "Case #" << qq << ": ";
		if (totalAvailable < goal) { cout << "IMPOSSIBLE\n"; }
		else {
			for (int i = 0; i < 4; i++) {
				int curVal = min(goal, minInk[i]);
				cout << curVal << ' ';
				goal -= curVal;
			}
			cout << '\n';
		}
	}
}
