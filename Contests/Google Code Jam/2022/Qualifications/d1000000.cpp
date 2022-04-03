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

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		int n; cin >> n;
		vector<int> s(n); for (auto& x : s) { cin >> x; }
		sort(s.begin(), s.end());

		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (ans < s[i]) { ans++; }
		}

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
