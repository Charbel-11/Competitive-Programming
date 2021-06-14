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

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> nums(n); 
		for (auto &x : nums) { cin >> x; }

		int res = 0;
		for (int k = 30; k >= 0; k--) {
			int one = 0, zero = 0;
			for (int i = 0; i < n; i++) {
				if (nums[i] & (1 << k)) { one++; }
				else { zero++; }
			}

			if (one % 2 == 0) { continue; }
			if (one == 1) { res = 1; break; }

			int mul = one / 2;
			if (mul % 2) {
				if (zero % 2) { res = 1; }
				else { res = 2; }
			}
			else { res = 1; }
			break;
		}

		if (res == 0) { cout << "DRAW\n"; }
		else if (res == 1) { cout << "WIN\n"; }
		else { cout << "LOSE\n"; }
	}
}