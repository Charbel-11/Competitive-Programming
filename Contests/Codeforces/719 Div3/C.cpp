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
		if (n == 2) { cout << -1 << '\n'; continue; }

		vector<int> ans(n * n, 0);
		int cur = 1;
		for (int i = 0; i < n * n; i += 2) {
			ans[i] = cur; cur++;
		}
		for (int i = 1; i < n * n; i += 2) {
			ans[i] = cur; cur++;
		}


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << ans[i * n + j] << ' ';
			}
			cout << '\n';
		}
	}
}
