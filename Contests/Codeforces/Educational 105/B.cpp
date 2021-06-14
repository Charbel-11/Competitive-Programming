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
		int n, U, R, D, L; cin >> n >> U >> R >> D >> L;

		bool OK = false;
		for (int i = 0; i < (1 << 4); i++) {
			int curU = U, curR = R, curD = D, curL = L;
			if (i & 1) { curU--; curL--; }
			if ((i >> 1) & 1) { curU--; curR--; }
			if ((i >> 2) & 1) { curD--; curL--; }
			if ((i >> 3) & 1) { curD--; curR--; }

			bool curOK = (curD >= 0 && curD <= n - 2 && curU >= 0 && curU <= n - 2 && curL >= 0 && curL <= n - 2 && curR >= 0 && curR <= n - 2);
			if (curOK) { OK = true; break; }
		}

		cout << (OK ? "YES" : "NO") << '\n';
	}
}