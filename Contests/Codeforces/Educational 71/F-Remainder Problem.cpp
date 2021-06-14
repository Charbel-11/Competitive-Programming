#include <iostream>
#include <vector>

using namespace std;

int main() {
	int q; cin >> q;
	vector<int> a(500002, 0); vector<vector<int>> answ(706);
	for (int i = 0; i < 706; i++) { answ[i].resize(706, 0); }

	for (int z = 0; z < q; z++) {
		int t, x, y; cin >> t >> x >> y;

		if (t == 1) {
			a[x] += y;
			for (int i = 1; i < 706; i++) { answ[i][x%i] += y; }
		}
		else {
			int res = 0;
			if (x < 706) { res = answ[x][y]; }
			else { for (int i = y; i < 500002; i += x) { res += a[i]; } }

			cout << res << endl;
		}
	}
}