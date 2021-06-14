#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int n; cin >> n;

	vector<int> a(n), b(n);
	for (auto &x : a) { cin >> x; }
	for (auto &x : b) { cin >> x; }

	vector<int> aMinus(n), bMinus(n);
	for (int i = 0; i < n; i++) {
		aMinus[i] = a[i] - b[i];
		bMinus[i] = b[i] - a[i];
	}

	sort(aMinus.begin(), aMinus.end());
	sort(bMinus.begin(), bMinus.end());

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ll count = 0;
		if (aMinus[i] > 0) { count--; }

		int idx = lower_bound(bMinus.begin(), bMinus.end(), aMinus[i]) - bMinus.begin();
		count += (ll)idx;
		ans += count;
	}

	cout << (ans/2ll) << endl;
}