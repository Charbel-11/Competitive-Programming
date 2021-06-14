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
		string a, b; cin >> a >> b;
		int n = a.size(), m = b.size();
		int ans = n + m;

		for (int i1 = 0; i1 < n; i1++) {
			for (int i2 = 0; i2 < n; i2++) {
				for (int j1 = 0; j1 < m; j1++) {
					for (int j2 = 0; j2 < m; j2++) {
						string s1 = a.substr(i1, i2 - i1 + 1);
						string s2 = b.substr(j1, j2 - j1 + 1);
						if (s1 == s2) { ans = min(ans, (n - (int)s1.size()) + (m - (int)s2.size())); }
					}
				}
			}
		}

		cout << ans << '\n';
	}
}