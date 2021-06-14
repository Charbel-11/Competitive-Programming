#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
vector<ll> x, v;
double  eps = 1e-7;

bool check(double t) {
	double maxL = -1e9, minR = 1e9;
	for (int i = 0; i < n; i++) {
		maxL = max(maxL, x[i] - v[i] * t);
		minR = min(minR, x[i] + v[i] * t);
	}
	return minR - maxL > eps;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n; x.resize(n); v.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> v[i];
	}

	double l = 0, r = 3e9;
	while (r - l > eps) {
		double mid = (l + r) / 2.0;
		if (check(mid)) { r = mid - eps; }
		else { l = mid + eps; }
	}
	
	cout << fixed << setprecision(7) << l << '\n';
}