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

	while (t--) {
		string s; cin >> s; int n = s.size();
		int x; cin >> x;
		string ans(n, '1');

		for (int i = 0; i < n; i++) {
			if (s[i] == '1') { continue; }

			int bef = i - x, nxt = i + x;
			if (bef >= 0) { ans[bef] = '0'; }
			if (nxt < n) { ans[nxt] = '0'; }
		}

		bool OK = true;
		for (int i = 0; i < n; i++) {
			if (s[i] == '0') { continue; }
			int bef = i - x, nxt = i + x;
			if (bef >= 0 && ans[bef] == '1') { continue; }
			if (nxt < n && ans[nxt] == '1') { continue; }
			OK = false; break;
		}

		if (!OK) { cout << -1 << '\n'; }
		else { cout << ans << '\n'; }
	}
}