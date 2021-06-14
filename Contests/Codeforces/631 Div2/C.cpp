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
	int n, m; cin >> n >> m;
	vector<int> range(m), ans(m);
	ll sum = 0;
	for (auto &x : range) { cin >> x; sum += x; }
	if (sum < n) { cout << -1 << endl; return 0; }

	int suffix = n + 1;
	for (int i = m - 1; i >= 0; i--) {
		suffix = min(suffix - 1, n - range[i] + 1);
		ans[i] = suffix;
	}
	if (suffix < 1) { cout << -1 << endl; return 0; }

	int r = 1;
	for (int i = 0; i < m; i++) {
		if (r >= ans[i]) { break; }
		ans[i] = r;	r = ans[i] + range[i];
	}

	for (auto &x : ans) { cout << x << " "; }cout << endl;
}