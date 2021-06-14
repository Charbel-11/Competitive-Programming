#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		ll totalSum = 0;
		vector<ll> a(n);
		for (auto &x : a) { cin >> x; totalSum += x; }

		ll maxOther = a[1], cur = a[1];
		for (int i = 2; i < n-1; i++) {
			cur += a[i];
			cur = max(cur, a[i]);	
			maxOther = max(maxOther, cur);
		}

		cur = a[0]; maxOther = max(maxOther, cur);
		for (int i = 1; i < n-1; i++) {
			cur += a[i];
			cur = max(cur, a[i]);
			maxOther = max(maxOther, cur);
		}

		cur = a[n-1]; maxOther = max(maxOther, cur);
		for (int i = n - 2; i >= 1; i--) {
			cur += a[i];
			cur = max(cur, a[i]);
			maxOther = max(maxOther, cur);
		}
		
		if (maxOther >= totalSum) { cout << "NO" << endl; }
		else { cout << "YES" << endl; }
	}
}