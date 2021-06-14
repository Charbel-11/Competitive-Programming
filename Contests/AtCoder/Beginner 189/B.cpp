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

	int n; cin >> n;
	double x; cin >> x;
	int ans = -1;
	double cur = 0, eps = 1e-6;

	for (int i = 1; i <= n; i++) {
		double v, p; cin >> v >> p;
		cur += v * p / 100.0;
		if (ans == -1 && cur - x > eps) { ans = i; }
	}

	cout << ans << '\n';
}