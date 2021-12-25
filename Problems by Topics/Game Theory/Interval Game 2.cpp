// https://atcoder.jp/contests/abc206/tasks/abc206_f

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <algorithm>
using namespace std;
typedef long long ll;

int GN[101][101];

int getGrundyNumber(int l, int r, vector<pair<int, int>>& intervals) {
	if (GN[l][r] != -1) { return GN[l][r]; }
	if (l > r) { return GN[l][r] = 0; }
	
	unordered_set<int> nextMoves;
	for (auto& interval : intervals) {
		if (interval.first > r) { break; }
		if (interval.first < l || interval.second > r) { continue; }

		int leftGN = getGrundyNumber(l, interval.first - 1, intervals);
		int rightGN = getGrundyNumber(interval.second + 1, r, intervals);
		nextMoves.insert(leftGN ^ rightGN);
	}

	int curGN = 0;
	while (nextMoves.count(curGN)) { curGN++; }
	return GN[l][r] = curGN;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<pair<int, int>> intervals;
		for (int i = 0; i < n; i++) {
			int l, r; cin >> l >> r; r--;
			intervals.push_back({ l, r });
		}
		sort(intervals.begin(), intervals.end());

		for (int i = 0; i < 101; i++)
			for (int j = 0; j < 101; j++)
				GN[i][j] = -1;

		if (getGrundyNumber(1, 100, intervals) > 0) { cout << "Alice" << '\n'; }
		else { cout << "Bob" << '\n'; }
	}
}