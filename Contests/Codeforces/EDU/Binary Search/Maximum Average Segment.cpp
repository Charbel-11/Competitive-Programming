#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, d;
vector<int> a;
int s, e;

bool check(double m) {
	vector<double> prefS(n);
	double curSum = 0, minP = 0;
	s = 0, e = d - 1;
	for (int i = 0; i < d - 1; i++) {
		curSum += a[i] - m;
		prefS[i] = curSum;
	}
	for (int i = d - 1; i < n; i++) {
		curSum += a[i] - m;
		prefS[i] = curSum;
		if (curSum >= minP) { e = i; return true; }
		if (minP > prefS[i - d + 1]) {
			minP = prefS[i - d + 1]; 
			s = i - d + 2;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> d;
	a.resize(n); for (auto& x : a) { cin >> x; }

	double l = 0, r = 1e7, eps = 1e-5;
	while (r-l>eps) {
		double mid = (l + r) / 2.0;
		if (check(mid)) { l = mid; }
		else { r = mid; }
	}

	check(l);
	cout << s + 1 << ' ' << e + 1 << '\n';
}