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

	vector<int> ans(46, 1e9);

	for (int i = 1; i < (1 << 9); i++) {
		int cur = 0, S = 0;
		for (int j = 0; j < 9; j++) {
			if (i & (1 << j)) {
				cur *= 10; cur += j + 1;
				S += j + 1;
			}
		}
		ans[S] = min(ans[S], cur);
	}

	int t; cin >> t;
	while (t--) {
		int s; cin >> s;
		cout << ans[s] << '\n';
	}
}
