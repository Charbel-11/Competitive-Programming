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
		int r, c; cin >> r >> c;
		vector<string> grid(2 * r + 1, string(2 * c + 1, '.'));

		for (int i = 0; i < 2 * r + 1; i += 2) {
			for (int j = 0; j < 2 * c + 1; j++) {
				if (j & 1) { grid[i][j] = '-'; }
				else { grid[i][j] = '+'; }
			}
		}

		for (int i = 1; i < 2 * r + 1; i += 2) {
			for (int j = 0; j < 2 * c + 1; j += 2) {
				grid[i][j] = '|';
			}
		}

		grid[0][0] = grid[0][1] = grid[1][0] = '.';

		cout << "Case #" << qq << ":\n";
		for (auto& s : grid) { cout << s << '\n'; }
	}
}
