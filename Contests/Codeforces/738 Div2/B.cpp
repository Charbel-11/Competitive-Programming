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
		string s; cin >> s;

		int start = -1;
		for (int i = 0; i < n; i++) {
			if (s[i] != '?') { start = i; break; }
		}

		if (start == -1) { start = 0; s[0] = 'R'; }
		for (int i = start - 1; i >= 0; i--) {
			if (s[i + 1] == 'R') { s[i] = 'B'; }
			else { s[i] = 'R'; }
		}

		for (int i = start + 1; i < n; i++) {
			if (s[i] != '?') { continue; }
			if (s[i - 1] == 'R') { s[i] = 'B'; }
			else { s[i] = 'R'; }
		}

		cout << s << '\n';
	}
}