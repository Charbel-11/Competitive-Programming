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

	int T; cin >> T;
	for (int q = 1; q <= T; q++) {
		int n; cin >> n;
		vector<int> h(n);
		for (auto &x : h) { cin >> x; }

		int ans = 0;
		for (int i = 1; i < n - 1; i++) {
			if (h[i] > h[i - 1] && h[i] > h[i + 1]) { ans++; }
		}

		cout << "Case #" << q << ": " << ans << endl;;
	}
}