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

	int n, x; cin >> n >> x;
	vector<int> prices(n); for (auto &x : prices) { cin >> x; }
	vector<int> pages(n); for (auto &x : pages) { cin >> x; }

	vector<int> dp(x + 1, 0);
	for (int i = 0; i < n; i++) {
		for (int j = x; j >= 0; j--) {
			int nxt = j + prices[i];
			if (nxt > x) { continue; }
			dp[nxt] = max(dp[nxt], dp[j] + pages[i]);
		}
	}

	cout << *max_element(dp.begin(), dp.end()) << '\n';
}