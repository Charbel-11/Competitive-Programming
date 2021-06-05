#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	vector<string> grid(8);
	for (auto &s : grid) { cin >> s; }

	int res = 0;
	vector<int> queens = { 0,1,2,3,4,5,6,7 };
	do {
		bool OK = true;
		for (int j = 0; j < 8; j++) {
			if (grid[queens[j]][j] == '*') { OK = false; break; }
		}
		if (!OK) { continue; }

		for (int j = 0; j < 8; j++) {
			int ni = queens[j] + 1, nj = j + 1;
			while (ni < 8 && nj < 8) {
				if (queens[nj] == ni) { OK = false; break; }
				ni++; nj++;
			}
			ni = queens[j] - 1, nj = j + 1;
			while (ni >= 0 && nj < 8) {
				if (queens[nj] == ni) { OK = false; break; }
				ni--; nj++;
			}
		}
		if (!OK) { continue; }

		res++;
	} while (next_permutation(queens.begin(), queens.end()));

	cout << res << '\n';
}