#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;
	for(int z = 0;z <T;z++){	
		int R, C, H, V; cin >> R >> C >> H >> V;
		vector<vector<char>> grid(R); for (auto& x : grid) { x.resize(C); }
		vector<int> rowC(R, 0), colC(C, 0); int total = 0;
		for (int i = 0; i < R; i++) {
			string s; cin >> s;
			for (int j = 0; j < C; j++) {
				grid[i][j] = (s[j] == '.' ? 0 : 1);
				rowC[i] += grid[i][j];
				colC[j] += grid[i][j];
				total += grid[i][j];
			}
		}

		bool possible = true;
		if (total % (H + 1) != 0 || total % (V + 1) != 0) { possible = false; }
		else if (total != 0) {
			vector<int> Hcut, Ccut;
			int divH = total / (H + 1);
			int cur = 0, tH = H + 1;
			Hcut.push_back(0);
			for (int i = 0; i < R; i++) {
				cur += rowC[i];
				if (cur == divH) {
					Hcut.push_back(i+1);
					cur = 0; tH--;
				}
			}
			if (cur != 0 || tH != 0) { possible = false; }

			int divC = total / (V + 1);
			cur = 0; int tV = V + 1;
			Ccut.push_back(0);
			for (int j = 0; j < C; j++) {
				cur += colC[j];
				if (cur == divC) { 
					Ccut.push_back(j+1);
					cur = 0; tV--; 
				}
			}
			if (cur != 0 || tV != 0) { possible = false; }

			if (possible) {
				int needed = total / ((H + 1)*(V + 1));
				for (int l = 0; l < H + 1; l++) {
					for (int k = 0; k < V + 1; k++) {
						cur = 0;
						for (int j = Ccut[k]; j < Ccut[k+1]; j++) {
							for (int i = Hcut[l]; i < Hcut[l+1]; i++) {
								cur += grid[i][j];
							}
						}
						if (cur != needed) { possible = false; break; }
					}
					if (cur != needed) { break; }
				}
			}
		}

		cout << "Case #" << z + 1 << ": " << (possible ? "POSSIBLE" : "IMPOSSIBLE") << endl;
	}
}