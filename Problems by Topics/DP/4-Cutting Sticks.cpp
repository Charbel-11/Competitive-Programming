#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int DP[52][52];
int n;
vector<int> cutPlaces;

//both start and end are included
int minCost(int start, int end) {
	if (start > end) { return 0; }
	if (DP[start][end] != -1) { return DP[start][end]; }

	int bestCost = 100000;
	for (int i = start; i < end + 1; i++) {
		int leftSide = minCost(start, i - 1); int rightSide = minCost(i + 1, end);
		int l = (start == 0) ? 0 : cutPlaces[start - 1]; int r = cutPlaces[end + 1];
		bestCost = min(bestCost, leftSide + rightSide + r - l);
	}

	DP[start][end] = bestCost; return bestCost;
}

void resetDP() {
	for (int i = 0; i < 52; i++) 
		for (int j = 0; j < 52; j++) 
			DP[i][j] = -1;
}

int main() {
	int length; cin >> length;
	while (length != 0) {
		cin >> n;
		cutPlaces.resize(n); for (auto &x : cutPlaces) { cin >> x; }
		cutPlaces.push_back(length);
		resetDP();

		cout << "The minimum cutting is " << minCost(0, n - 1) << "." << endl;

		cin >> length;
	}
}