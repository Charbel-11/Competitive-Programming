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
		int r, c; cin >> r >> c;
		vector<string> grid(r);
		for (auto& s : grid) { cin >> s; }

		int a, b; cin >> a >> b;
		vector<string> pattern(a);
		for (auto& s : pattern) { cin >> s; }

		int ans = 0;
		for (int i = 0; i + a - 1 < r; i++) {
			for (int j = 0; j + b - 1 < c; j++) {
				bool OK = true;
				for (int l = 0; l < a; l++) {
					for (int m = 0; m < b; m++) {
						if (pattern[l][m] == '?') { continue; }
						if (pattern[l][m] != grid[i + l][j + m]) { OK = false; break; }
					}
				}
				ans += OK;
			}
		}

		cout << ans << '\n';
	}
}