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
	vector<ll> a(n), b(n);
	for (auto& x : a) { cin >> x; }
	for (auto& x : b) { cin >> x; }

	vector<ll> c(n); c[0] = a[0] * b[0];
	ll maxA = a[0];
	for (int i = 1; i < n; i++) {
		c[i] = c[i - 1];
		c[i] = max(c[i], a[i] * b[i]);
		c[i] = max(c[i], maxA * b[i]);
		maxA = max(maxA, a[i]);
	}

	for (auto& x : c) { cout << x << '\n'; }
}