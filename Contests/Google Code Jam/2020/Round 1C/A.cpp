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

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int x, y; cin >> x >> y;
		string s; cin >> s;

		bool OK = false; int ans = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'N') { y++; }
			else if (s[i] == 'S') { y--; }
			else if (s[i] == 'E') { x++; }
			else if (s[i] == 'W') { x--; }

			int needed = abs(x) + abs(y);
			if (needed <= i + 1) { ans = i + 1; OK = true; break; }
		}

		cout << "Case #" << q << ": ";
		if (!OK) { cout << "IMPOSSIBLE" << endl; }
		else { cout << ans << endl; }
	}
}