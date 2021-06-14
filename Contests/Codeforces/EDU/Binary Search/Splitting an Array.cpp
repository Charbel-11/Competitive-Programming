#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k;
vector<ll> a;

bool check(ll maxS) {
	int curK = k - 1;
	ll curS = 0;
	for (int i = 0; i < n; i++) {
		if (curS + a[i] > maxS) {
			curS = 0; curK--;
		}
		curS += a[i];
	}
	return curK >= 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	a.resize(n); for (auto& x : a) { cin >> x; }

	ll l = *max_element(a.begin(), a.end()), r = 1e15;
	while (l < r) {
		ll mid = (l + r) / 2;
		if (check(mid)) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << '\n';
}