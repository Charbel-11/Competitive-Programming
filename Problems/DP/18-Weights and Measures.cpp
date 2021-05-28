#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
	vector<pair<int, int>> turtles;
	int w, c;
	while (true) {
		cin >> w; if (cin.fail()) { break; }
		cin >> c;
		turtles.push_back({ c, w });
	}

	int n = turtles.size();
	sort(turtles.begin(), turtles.end());

	vector<int> DP; DP.resize(n + 2, INT_MAX); DP[0] = 0;

	for (int i = 0; i < n; i++) {
		//Start k from the end to avoid using the same turtle more than once in the stacks
		for (int k = n; k > 0; k--) { 
			//Check if we can update the weight to stack k turtles by using the ith turtle as base
			if (DP[k - 1] != INT_MAX && turtles[i].first >= DP[k - 1] + turtles[i].second) {
				DP[k] = min(DP[k], DP[k - 1] + turtles[i].second);
			}
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		if (DP[i] != INT_MAX) { cout << i << endl; break; }
	}
}
