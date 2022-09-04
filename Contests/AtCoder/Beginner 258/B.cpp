#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;

ll getNumber(int i, int j, int dx, int dy, vector<string>& A) {
	ll ans = 0;
	for (int kk = 0; kk < n; kk++) {
		ans *= 10; ans += (A[i][j] - '0');
		i += dx; j += dy;
		i %= n; j %= n;
		if (i < 0) { i += n; }
		if (j < 0) { j += n; }
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n;
	vector<string> A(n);
	for (auto& s : A) { cin >> s; }

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (auto dx : { -1,0, 1 }) {
				for (auto dy : { -1, 0, 1 }) {
					if (dx == 0 && dy == 0) { continue; }
					ans = max(ans, getNumber(i, j, dx, dy, A));
				}
			}
		}
	}

	cout << ans << '\n';
}
