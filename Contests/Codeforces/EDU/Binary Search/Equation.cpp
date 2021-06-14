#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	double c; cin >> c;
	double l = 0, r = c, eps = 1e-8;
	while (r - l > eps) {
		double mid = (l + r) / 2.0;
		double x = mid * mid;
		double guess = x * x + mid;
		if (guess - c > eps) { r = mid; }
		else { l = mid; }
	}

	cout << fixed << setprecision(7) << l * l << '\n';
}