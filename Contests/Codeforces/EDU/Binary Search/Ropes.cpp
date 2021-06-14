#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<double> a;
int n, k;

bool check(double len) {
	int pieces = 0;
	for (auto& x : a) {
		pieces += x / len;
		if (pieces >= k) { return true; }
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	a.resize(n); for (auto& x : a) { cin >> x; }

	double l = 0, r = 1e7, eps = 1e-7;
	while (r - l > eps) {
		double mid = (r + l) / 2.0;
		if (check(mid)) { l = mid; }
		else { r = mid; }
	}
	cout << fixed << setprecision(7) << l << '\n';
}