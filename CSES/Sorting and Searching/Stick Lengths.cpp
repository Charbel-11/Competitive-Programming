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

	int n; cin >> n;
	vector<ll> sticks(n);
	for (auto &x : sticks) { cin >> x; }
	sort(sticks.begin(), sticks.end());

	ll diff = 0;
	for (int i = 1; i < n; i++) { diff += sticks[i] - sticks[0]; }

	ll res = diff;
	for (int i = 1; i < n; i++) {
		diff -= (sticks[i] - sticks[i - 1])*(n - i);
		diff += (sticks[i] - sticks[i - 1])*i;

		res = min(res, diff);
	}

	cout << res << '\n';
}