#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, q; cin >> n >> q;
	vector<ll> nums(n);
	for (auto &x : nums) { cin >> x; }

	vector<ll> pref(n, 0); pref[0] = nums[0];
	for (int i = 1; i < n; i++) { pref[i] = pref[i - 1] + nums[i]; }

	while (q--) {
		int a, b; cin >> a >> b; a--; b--;
		cout << pref[b] - (a ? pref[a - 1] : 0) << '\n';
	}
}