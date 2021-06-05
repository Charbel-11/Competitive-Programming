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

const int M = (int)1e5 + 2;
bool sums[M + 1];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	sums[0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = M - 1; j >= 0; j--) {
			int nxt = j + nums[i];
			if (j > M) { continue; }
			sums[nxt] |= sums[j];
		}
	}

	vector<int> ans;
	for (int i = 1; i <= M; i++) {
		if (sums[i]) { ans.push_back(i); }
	}

	cout << ans.size() << '\n';
	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}