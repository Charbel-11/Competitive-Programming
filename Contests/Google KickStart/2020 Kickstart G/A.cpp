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
		string s; cin >> s;
		int n = s.size();

		vector<int> kick(n + 1, 0);
		for (int i = 0; i < n-3; i++) {
			string curS = s.substr(i, 4);
			if (curS == "KICK") { kick[i + 3]++; }
		}

		for (int i = 1; i < n; i++) { kick[i] += kick[i - 1]; }

		ll ans = 0;

		for (int i = 0; i < n - 4; i++) {
			string curS = s.substr(i, 5);
			if (curS == "START") { ans += kick[i]; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}