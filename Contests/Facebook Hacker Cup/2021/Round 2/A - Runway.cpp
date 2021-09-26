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
		int n, m; ifs >> n >> m;

		vector<pair<int, int>> curState;
		for (int i = 0; i < m; i++) {
			int s; ifs >> s; curState.push_back({ s, 1 });
		}
		sort(curState.begin(), curState.end());

		int ans = 0;
		for (int i = 0; i < n; i++) {
			vector<int> cur(m); for (auto& x : cur) { ifs >> x; }
			vector<pair<int, int>> nextState;
			sort(cur.begin(), cur.end());

			vector<pair<int, int>> unmatchedCur;
			vector<int> unmatchedNext;
			int i1 = 0;
			for (int j = 0; j < m; j++) {
				if (i1 >= m) { unmatchedNext.push_back(cur[j]); continue; }

				if (curState[i1].first == cur[j]) { nextState.push_back(curState[i1]); i1++; continue; }
				if (curState[i1].first > cur[j]) { unmatchedNext.push_back(cur[j]); }
				else { unmatchedCur.push_back(curState[i1]); i1++; j--; }
			}
			while (i1 < m) { unmatchedCur.push_back(curState[i1++]); }

			for (int j = 0; j < unmatchedNext.size(); j++) {
				if (!unmatchedCur[j].second) { ans++; }
				nextState.push_back({ unmatchedNext[j], 0 });
			}

			curState = nextState;
			sort(curState.begin(), curState.end());
		}

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}