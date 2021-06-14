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
	while (t--) {
		int n, m; cin >> n >> m;
		vector<pair<int, int>> b(m);
		for (auto& p : b) { cin >> p.second >> p.first; p.second--; }
		sort(b.begin(), b.end());
		b.push_back({ n + 1, 0 });
		b.push_back({ n + 1, 1 });
		m = b.size();

		bool OK = true;

		int i = 0;
		while (i < m) {
			bool curCol[2], nxtCol[2];
			int curColIdx = b[i].first, nxtColIdx = -1;
			curCol[0] = curCol[1] = nxtCol[0] = nxtCol[1] = 0;
			curCol[b[i].second] = 1;

			for (int j = i + 1; j <= min(i + 3, m - 1); j++) {
				if (b[j].first == curColIdx) { curCol[b[j].second] = 1; }
				else if (nxtColIdx == -1) {
					nxtColIdx = b[j].first;
					nxtCol[b[j].second] = 1;
				}
				else if (nxtColIdx == b[j].first) { nxtCol[b[j].second] = 1; }
				else { break; }
			}

			if (curCol[0] && curCol[1]) { i += 2; continue; }
			if (nxtCol[0] && nxtCol[1]) { OK = false; break; }
			int rowToAdd = 0, diff = nxtColIdx - curColIdx;
			if (curCol[0]) { rowToAdd = 1; }
			
			if (nxtCol[0]) {
				if (rowToAdd == 1 && diff % 2 == 0) { OK = false; break; }
				if (rowToAdd == 0 && diff % 2) { OK = false; break; }
			}
			if (nxtCol[1]) {
				if (rowToAdd == 0 && diff % 2 == 0) { OK = false; break; }
				if (rowToAdd == 1 && diff % 2) { OK = false; break; }
			}
			i += curCol[0] + curCol[1] + nxtCol[0] + nxtCol[1];
		}

		cout << (OK ? "YES" : "NO") << '\n';
	}
}