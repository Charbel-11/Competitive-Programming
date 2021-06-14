#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n;
ll k;
ll l[50], r[50];

bool smaller(ll num) {
	ll res = 0;
	for (int i = 0; i < n; i++) {
		if (num < l[i]) { continue; }
		res += min(num, r[i]) - l[i] + 1;
		if (res >= k) { return true; }
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k; k++;
	for (int i = 0; i < n; i++) {
		cin >> l[i] >> r[i];
	}

	ll lV = -2e9, rV = 2e9;
	while (lV < rV) {
		ll mid = (lV + rV) >> 1;
		if (smaller(mid)) { rV = mid; }
		else { lV = mid + 1; }
	}
	cout << lV << '\n';
}