#include <iostream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<string> grid(n, string(n, '.'));

	vector<int> a(n), b(n);
	priority_queue<pair<int, int>> pq;
	for (int i = 0; i < n; i++) { cin >> a[i]; }
	for (int i = 0; i < n; i++) {
		cin >> b[i];
		if (b[i]) { pq.push({ b[i], i }); }
	}

	bool OK = true;
	for (int i = 0; i < n; i++) {
		vector<pair<int, int>> curUsed;
		for (int j = 0; j < a[i]; j++) {
			if (pq.empty()) { OK = false; break; }

			int colRem = pq.top().first;
			int colIdx = pq.top().second;
			grid[i][colIdx] = 'X';

			if (colRem > 1) { curUsed.push_back({ colRem - 1, colIdx }); }
			pq.pop();
		}
		if (!OK) { break; }
		for (auto& p : curUsed) { pq.push(p); }
	}

	if (!OK || !pq.empty()) { cout << -1 << '\n'; }
	else {
		for (auto& s : grid) { cout << s << '\n'; }
	}
}