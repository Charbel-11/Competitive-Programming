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

	ll n; cin >> n;
	ll midPos = (n * n + 1) / 2;

	ll l = 1, r = n * n;
	while (l < r) {
		ll mid = (l + r) >> 1, curLEQ = 0;
		for (int i = 1; i <= n; i++) {
			curLEQ += min(n, (mid / i));
		}

		//Need to find the first one since this one must be in the table
		if (curLEQ >= midPos) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << '\n';
}