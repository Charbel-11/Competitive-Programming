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

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		vector<vector<int>> G(3, vector<int>(3, 0));
		for (int i = 0; i < 3; i++) { cin >> G[0][i]; }
		cin >> G[1][0] >> G[1][2];
		for (int i = 0; i < 3; i++) { cin >> G[2][i]; }

		map<int, int> freq;
		int ans = 0;
		for (int i = 0; i < 3; i++) {
			if (i == 1) {
				int diff = G[1][2] - G[1][0];
				if (diff % 2 == 0) { freq[G[1][0] + diff/2]++; }

				diff = G[2][1] - G[0][1];
				if (diff % 2 == 0) { freq[G[0][1] + diff/2]++; }

				diff = G[2][2] - G[0][0];
				if (diff % 2 == 0) { freq[G[0][0] + diff/2]++; }

				diff = G[2][0] - G[0][2];
				if (diff % 2 == 0) { freq[G[0][2] + diff/2]++; }
			}
			else {
				if (G[i][1] - G[i][0] == G[i][2] - G[i][1]) { ans++; }
				if (G[1][i] - G[0][i] == G[2][i] - G[1][i]) { ans++; }
			}
		}

		int add = 0;
		for (auto& p : freq) { add = max(add, p.second); }
		ans += add;
		
		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
