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

int dist[26][26];

void resetDist() {
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			if (i != j) { dist[i][j] = -1; }
			else { dist[i][j] = 0; }
		}
	}
}

void findAPSP() {
	for (int k = 0; k < 26; k++) {
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				if (dist[i][k] == -1 || dist[k][j] == -1) { continue; }
				if (dist[i][j] == -1) { dist[i][j] = dist[i][k] + dist[k][j]; }
				else { dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); }
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		string s; ifs >> s;
		int ans = INT_MAX;

		resetDist();
		int k; ifs >> k;
		for (int i = 0; i < k; i++) {
			string cur; ifs >> cur;
			int u = cur[0] - 'A', v = cur[1] - 'A';
			if (u != v) { dist[u][v] = 1; }
		}
		
		findAPSP();

		for (char c = 'A'; c <= 'Z'; ++c) {
			int curAns = 0; bool OK = true;

			for (auto& curC : s) {
				if (dist[curC - 'A'][c - 'A'] == -1) { OK = false; break; }
				curAns += dist[curC - 'A'][c - 'A'];
			}
			
			if (OK) { ans = min(ans, curAns); }
		}

		ofs << "Case #" << qq << ": ";
		if (ans == INT_MAX) { ofs << -1 << '\n'; }
		else { ofs << ans << '\n'; }
	}
}