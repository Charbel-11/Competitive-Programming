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

vector<int> digits(int n) {
	vector<int> res;
	while (n) {
		if (n % 10) res.push_back(n % 10);
		n /= 10;
	}
	return move(res);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> dp(n + 1, n + 1); dp[0] = 0; 
	for (int i = 1; i <= min(n, 9); i++) { dp[i] = 1; }

	for (int i = 10; i <= n; i++) {
		vector<int> d = digits(i);
		for (auto &x : d) { dp[i] = min(dp[i], dp[i - x] + 1); }
	}

	cout << dp[n] << '\n';
}