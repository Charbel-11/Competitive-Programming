#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		int N; cin >> N;
		vector<vector<char>> grid(N);
		for (auto &x : grid) { x.resize(N); }

		set<pair<int, int>> m;
		for (int i = 0; i < N; i++) {
			string cur; cin >> cur;
			for (int j = 0; j < N; j++) {
				grid[i][j] = cur[j];
				if (cur[j] == '.') {
					m.insert({ i,j });
				}
			}
		}

		int res = 0;
		while (!m.empty()) {
			auto it = m.begin();
			int i = it->first, j = it->second;
			res++;

			pair<int, int> c1, c2;
			c1 = c2 = { 0,0 };

			while (i < N - 1 && j > 0) { i++; j--; }
			while (i < N && j < N && i>=0 && j>=0) {
				if (grid[i][j] == '.') { c1.first++; }
				else { c1.second++; }
				i--; j++;
			}

			i = it->first, j = it->second;
			while (i < N - 1 && j < N - 1) { i++; j++; }
			while (i >= 0 && j >= 0) {
				if (grid[i][j] == '.') { c2.first++; }
				else { c2.second++; }
				i--; j--;
			}

			i = it->first, j = it->second;
			if (c1.first - c1.second > c2.first - c2.second) {
				while (i < N - 1 && j > 0) { i++; j--; }
				while (i < N && j < N && i >= 0 && j >= 0) {
					if (grid[i][j] == '.') {
						grid[i][j] = '#';
						m.erase({ i, j });
					}
					else { 
						grid[i][j] = '.';
						m.insert({ i,j });
					}
					i--; j++;
				}
			}
			else {
				while (i < N - 1 && j < N - 1) { i++; j++; }
				while (i >= 0 && j >= 0) {
					if (grid[i][j] == '.') {
						grid[i][j] = '#';
						m.erase({ i, j });
					}
					else {
						grid[i][j] = '.';
						m.insert({ i,j });
					}
					i--; j--;
				}
			}
		}
		cout << "Case #" << z + 1 << ": " << res << endl;
	}
}