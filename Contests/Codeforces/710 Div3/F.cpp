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
		int n; cin >> n;
		vector<pair<int, int>> points(n);
		for (int i = 0; i < n; i++) { cin >> points[i].first; }
		for (int i = 0; i < n; i++) { cin >> points[i].second; }
		sort(points.begin(), points.end());

		int ans = 0;
		pair<int, int> curP = { 1,1 };
		for (int i = 0; i < points.size(); i++) {
			auto& p = points[i];
			int difC = p.second - curP.second, difR = p.first - curP.first;
			if ((curP.first + curP.second) % 2) {
				difR -= difC;
				ans += ((difR + 1) / 2);
			}
			else {
				if (difC == difR) { ans += difC; }
				else {
					curP = { curP.first + 1, curP.second };
					i--; continue;
				}
			}

			curP = p;
		}

		cout <<ans << '\n';
	}
}