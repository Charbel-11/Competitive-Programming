#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll n, k;
vector<ll> a, b;
ll smaller(ll num){
	int j = 0;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		while (j < n && a[i] + b[j] <= num) { j++; }
		ans += j;
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	a.resize(n); b.resize(n);
	for (auto& x : a) { cin >> x; }
	for (auto& x : b) { cin >> x; }
	sort(a.rbegin(), a.rend());
	sort(b.begin(), b.end());

	ll l = 0, r = 1e10;
	while (l < r) {
		ll mid = (l + r) >> 1;
		if (smaller(mid) >= k) { r = mid; }
		else { l = mid + 1; }
	}
	cout << l << '\n';
}