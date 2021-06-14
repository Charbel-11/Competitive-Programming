#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;

	vector<vector<bool>> grid(2); grid[0].resize(n, 0); grid[1].resize(n, 0);
	set<pair<pair<int, int>, pair<int,int>>> lava;
	bool possible = true;
	while (q--) {
		int r, c; cin >> r >> c; r--; c--;
		if (!grid[r][c]) {
			grid[r][c] = 1;

			int otherRow = (r + 1) % 2;
			if (grid[otherRow][c]) {
				possible = false;
				lava.insert({ { r, c }, {otherRow, c} });
				lava.insert({ {otherRow, c}, {r,c} });
			}
			if (c != 0 && grid[otherRow][c - 1]) {
				possible = false;
				lava.insert({ { r, c }, {otherRow, c-1} });
				lava.insert({ {otherRow, c-1}, {r,c} });
			}
			if (c != n - 1 && grid[otherRow][c + 1]) {
				possible = false;
				lava.insert({ { r, c }, {otherRow, c + 1} });
				lava.insert({ {otherRow, c + 1}, {r,c} });
			}
		}
		else {
			grid[r][c] = 0;

			int otherRow = (r + 1) % 2;
			if (grid[otherRow][c]) {
				lava.erase({ {r,c}, {otherRow, c} });
				lava.erase({ {otherRow, c}, {r,c} });
			}
			if (c != 0 && grid[otherRow][c - 1]) {
				lava.erase({ { r, c }, {otherRow, c - 1} });
				lava.erase({ {otherRow, c - 1}, {r,c} });
			}
			if (c != n - 1 && grid[otherRow][c + 1]) {
				lava.erase({ { r, c }, {otherRow, c + 1} });
				lava.erase({ {otherRow, c + 1}, {r,c} });
			}

			possible = lava.empty();
		}

		cout << (possible ? "Yes" : "No") << endl;
	}
}