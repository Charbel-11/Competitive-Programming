#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

int main() {
	int n, k; cin >> n >> k;
	vector<ll> a(n);
	map<int, int> m; bool zero = false;
	for (auto &x : a) { cin >> x; m[x]++; if (m[x] == k)zero = true; }

	if (zero) { cout << 0 << endl; return 0; }
	sort(a.begin(), a.end());
	
	ll leftAns = 0, rightAns = 0, midAns = 0;
	ll duplicate = 0;
	for (int i = 1; i < k; i++) {
		leftAns += i * (a[i] - a[i - 1]);
		duplicate += a[i] == a[k - 1];
	}
	leftAns -= (m[a[k - 1]] - duplicate);
	ll ans = max(leftAns, 0ll);

	duplicate = 0;
	for (int i = n - 2; i >= n - k; i--) {
		rightAns += (n - i - 1)*(a[i + 1] - a[i]);
		duplicate += a[i] == a[n - k];
	}
	rightAns -= (m[a[n - k]] - duplicate);
	ans = min(ans, max(rightAns, 0ll));

	ll target = (n % 2) ? a[n / 2] : (a[n / 2 - 1] + a[n / 2]) / 2;
	for (int i = 0; i < n; i++) {
		midAns += abs(target - a[i]);
	}
	midAns -= (n - k); midAns = max(midAns, 0ll);
	ans = min(ans, midAns);

	cout << ans << endl;
}