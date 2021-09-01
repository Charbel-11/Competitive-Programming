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

	int n; ll s; cin >> n >> s;
	vector<ll> w(n), c(n);
	for (auto& x : w) { cin >> x; }
	for (auto& x : c) { cin >> x; }

	ll ans = 0;
	int l = 0; ll curW = 0, curC = 0;
	for (int r = 0; r < n; r++) {
		curW += w[r]; curC += c[r];
		while (curW > s) { curW -= w[l]; curC -= c[l]; ++l; }

		ans = max(ans, curC);
	}

	cout << ans << '\n';
}