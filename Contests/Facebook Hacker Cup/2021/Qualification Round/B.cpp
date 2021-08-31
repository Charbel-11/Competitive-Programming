#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; ifs >> n;
		vector<string> grid(n);
		for (auto& s : grid) { ifs >> s; }
		
		set<pair<int, int>> candForOne;
		int minNeeded = n, minCnt = 0;
		for (int i = 0; i < n; i++) {
			int curNeeded = 0, emptyIdx = -1; bool OK = true;
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == 'O') { OK = false; break; }
				else if (grid[i][j] == '.') { curNeeded++; emptyIdx = j; }
			}
			if (OK) {
				if (curNeeded < minNeeded) { minNeeded = curNeeded; minCnt = 1; }
				else if (curNeeded == minNeeded) { minCnt++; }

				if (curNeeded == 1) { candForOne.insert({ i,emptyIdx }); }
			}
		}

		for (int j = 0; j < n; j++) {
			int curNeeded = 0, emptyIdx = -1; bool OK = true;
			for (int i = 0; i < n; i++) {
				if (grid[i][j] == 'O') { OK = false; break; }
				else if (grid[i][j] == '.') { curNeeded++; emptyIdx = i; }
			}
			if (OK) {
				if (curNeeded < minNeeded) { minNeeded = curNeeded; minCnt = 1; }
				else if (curNeeded == minNeeded) { minCnt++; }

				if (curNeeded == 1) { candForOne.insert({ emptyIdx, j }); }
			}
		}

		if (minNeeded == 1) { minCnt = candForOne.size(); }

		ofs << "Case #" << qq << ": ";
		if (minCnt == 0) { ofs << "Impossible" << '\n'; }
		else { ofs << minNeeded << " " << minCnt << '\n'; }
	}
}