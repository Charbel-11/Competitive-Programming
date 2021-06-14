#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long double ld;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m, k; cin >> n >> m >> k;
	vector<ld> a(n + m + 1, 0), c(n + m + 1, 0);
	vector<bool> t(n + m + 1, 0);
	for (int i = 0; i < k; i++) { int idx; cin >> idx; t[idx] = 1; }
	
	int l = 1;
	for (int r = 1; r < n; r++) {
		if (!t[r]) { l = r + 1; continue; }
		if (r - l + 1 == m) { cout << -1 << '\n'; exit(0); }
	}
	
	ld sufA = 0, sufC = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (t[i]) { a[i] = 1; c[i] = 0; }
		else { a[i] = (sufA / m); c[i] = 1 + (sufC / m); }
		sufA += a[i] - a[i + m]; sufC += c[i] - c[i + m];
	}

	cout << fixed << setprecision(6) << c[0] / (1 - a[0]) << '\n';
}