#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int q; cin >> q;

	for (int z = 0; z < q; z++) {
		int c, m, x; cin >> c >> m >> x;

		if (c < m) {
			x += (m - c);
			m = c;
		}
		else {
			x += (c - m);
			c = m;
		}

		if (x >= c) {
			cout << c << endl;
		}
		else {
			int res = x;
			c -= x; m -= x;
			res += (c + m) / 3;
			cout << res << endl;
		}
	}
}