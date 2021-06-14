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
	int x; cin >> x;
	for (int qq = 1; qq <= t; qq++) {
		int w, e; cin >> w >> e;

		string ans = "R";
		int r = 1, s = 0, p = 0;
		double eps = 1e-6;

		for (int i = 2; i <= 60; i++) {
			double probR = (double)s / (i - 1.0), probP = (double)r / (i - 1.0), probS = (double)p / (i - 1.0);

			vector<pair<double, int>> v = { {probR, 0}, {probP, 1}, {probS, 2} };
			sort(v.rbegin(), v.rend());

			if (v[1].first > v[2].first + eps && v[0].first + v[1].first > 0.75 && e == w) {
				int c1 = v[0].second, c2 = v[1].second, choice = 0;

				if (c1 == 0) {
					if (c2 == 1) { choice = 1; }
					else if (c2 == 2) { choice = 0; }
				}
				else if (c1 == 1) {
					if (c2 == 0) { choice = 1; }
					else if (c2 == 2) { choice = 2; }
				}
				else {
					if (c2 == 0) { choice = 0; }
					else if (c2 == 1) { choice = 2; }
				}

				if (choice == 1) { ans.push_back('P'); p++; }
				else if (choice == 2) { ans.push_back('S'); s++; }
				else { ans.push_back('R'); r++; }
			}
			else if (v[0].first > v[1].first + eps) {
				if (v[0].second == 0) { ans.push_back('P'); p++; }
				else if (v[0].second == 1) { ans.push_back('S'); s++; }
				else { ans.push_back('R'); r++; }
			}
			else { ans.push_back('R'); r++; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
