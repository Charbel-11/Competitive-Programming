#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;

bool check(ll w, ll h, ll n, ll mid) {
	ll col = mid / w;
	ll row = mid / h;
	if (col >= n && row) { return true; }
	if (row >= n && col) { return true; }
	return col * row >= n;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll w, h, n; cin >> w >> h >> n;
	ll l = 0, r = 1e18;
	while (l < r) {
		ll mid = r - (r - l + 1) / 2;
		if (check(w, h, n, mid)) {
			r = mid;
		}
		else { l = mid + 1; }
	}
	cout << l << '\n';
}