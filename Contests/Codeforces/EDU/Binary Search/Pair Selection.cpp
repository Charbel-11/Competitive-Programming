#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k;
vector<double> a, b;

bool check(double m) {
	vector<double> newA(n);
	for (int i = 0; i < n; i++) {
		newA[i] = a[i] - m * b[i];
	}
	sort(newA.rbegin(), newA.rend());
	double ans = 0;
	for (int i = 0; i < k; i++) {
		ans += newA[i];
	}
	return ans >= 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	a.resize(n); b.resize(n);
	for (int i = 0; i < n; i++) { cin >> a[i] >> b[i]; }
	double l = 0, r = 1e10, eps = 1e-7;
	while (r - l > eps) {
		double mid = (l + r) / 2.0;
		if (check(mid)) { l = mid; }
		else { r = mid; }
	}

	cout << fixed << setprecision(7) << l << '\n';
}