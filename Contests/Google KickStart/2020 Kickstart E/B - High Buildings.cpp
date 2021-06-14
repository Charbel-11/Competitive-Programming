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
		int n, a, b, c; cin >> n >> a >> b >> c;
		cout << "Case #" << qq << ": ";
		a -= c; b -= c;
		if (a + b + c > n || (n > 1 && a == 0 && b == 0 && c == 1)) { cout << "IMPOSSIBLE\n"; continue; }

		vector<int> ans(n, n);
		for (int i = 0; i < a; i++) { ans[i] = i + 1; }
		for (int i = n - 1; i > n - b - 1; i--) { ans[i] = n - i; }

		if (a + b + c != n) {
			int r = n - a - b - c;
			if (c > 1) {
				for (int i = a + 1; i < a + 1 + r; i++) { ans[i] = n - 1; }
			}
			else {
				if (n == 2) {
					if (a) { ans[0] = 1; ans[1] = 2; }
					else { ans[0] = 2; ans[1] = 1; }
				}
				else {
					if (a) {
						if (a == 1) { ans[0]++; }
						ans[a] = ans[a - 1] - 1;
						for (int i = a + 1; i < a + r; i++) { ans[i] = ans[i - 1]; }
					}
					else {
						if (b == 1) { ans[n - 1]++; }
						ans[n - b - 1] = ans[n - b] - 1;
						for (int i = n - b - 2; i > n - b - 1 - r; i--) { ans[i] = ans[i + 1]; }
					}
				}
			}
		}
		for (auto &x : ans) { cout << x << ' '; }cout << '\n';
	}
}