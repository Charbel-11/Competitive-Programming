//https://atcoder.jp/contests/abc164/tasks/abc164_d
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

	string s; cin >> s;
	ll ans = 0, cur = 0, pow10 = 1;
	vector<ll> dp(2019, 0); dp[0] = 1;
	for (int i = s.size() - 1; i >= 0; i--) {
		cur += (pow10 * (s[i] - '0')) % 2019; cur %= 2019;
		pow10 *= 10; pow10 %= 2019;
		ans += dp[cur]; dp[cur]++;
	}
	cout << ans << '\n';
}