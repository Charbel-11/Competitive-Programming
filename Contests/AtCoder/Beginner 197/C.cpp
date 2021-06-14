#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> A(n); for (auto& x : A) { cin >> x; }

	int ans = INT_MAX;
	for (int m = 0; m < (1 << n-1); m++) {
		int curX = 0, curO = A[0];
		for (int k = 0; k < n - 1; k++) {
			if (!(m & (1 << k))) { curO |= A[k + 1]; continue; }
			curX ^= curO; curO = A[k + 1];
		}
		curX ^= curO;
		ans = min(ans, curX);
	}

	cout << ans << '\n';
}