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

	int n, minD; cin >> n >> minD;
	vector<int> d(n); for (auto& x : d) { cin >> x; }

	ll ans = 0; int r = 0;
	for (int l = 0; l < n; l++) {
		while (r < n && d[r] - d[l] <= minD) { r++; }
		if (r == n) { break; }

		ans += (n - r);
	}

	cout << ans << '\n';
}