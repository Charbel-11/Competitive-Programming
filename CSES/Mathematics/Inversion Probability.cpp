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

	int n; cin >> n;
	vector<double> r(n); for (auto& x : r) { cin >> x; }

	double ans = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= r[i]; j++) {
			double curP = 1 / r[i], curE = 0;
			for (int k = 0; k < i; k++) {
				if (j >= r[k]) { continue; }
				curE += (r[k] - j) / r[k];
			}
			ans += curE * curP;
		}
	}

	cout << fixed << setprecision(6) << ans << '\n';
}