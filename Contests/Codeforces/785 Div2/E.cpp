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

	int n, k; cin >> n >> k;
	vector<int> B(n); for (auto& x : B) { cin >> x; }
	vector<bool> ans(1 << 20, false);

	ll modPower = (1ll << 20);

	for (int l = 0; l < n; l++) {
		ll curP = 1;
		for (int r = l; r < n; r++) {
			if (r == l) { curP *= B[r]; }
			else {
				if (B[r] >= 20) { break; }
				curP *= (1ll << B[r]);
			}
			if (curP >= modPower) { break; }

			int remChoices = n - 1 - (r - l) - 2, reqXor = k - 2;
			if (l == 0) { remChoices++; reqXor++; }
			if (r == n - 1) { remChoices++; reqXor++; }

			if (remChoices >= reqXor && (remChoices == 0 || (reqXor > 0 && ((remChoices - 1) | (reqXor - 1)) == (remChoices - 1)))) {
				ans[curP] = !ans[curP];
			}
		}
	}

	reverse(ans.begin(), ans.end());
	string s = ""; int idx = 0;
	while (idx < ans.size() && !ans[idx]) { idx++; }
	for (; idx < ans.size(); idx++) {
		s.push_back(ans[idx] ? '1' : '0');
	}
	cout << (s == "" ? "0" : s) << '\n';
}