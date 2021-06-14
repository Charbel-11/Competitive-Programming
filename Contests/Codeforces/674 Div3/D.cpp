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
	vector<ll> a(n); for (auto &x : a) { cin >> x; }
	map<ll, int> m; m[0] = -1;
	int ans = 0;
	ll curSum = 0;

	for (int i = 0; i < n; i++) {
		curSum += a[i];
		if (m.count(curSum)) {
			m.clear(); m[0] = i - 1;
			curSum = a[i]; ans++; 
		}
		m[curSum] = i;
	}

	cout << ans << '\n';
}