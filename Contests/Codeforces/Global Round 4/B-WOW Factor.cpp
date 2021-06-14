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

	string s; cin >> s;
	vector<ll> dp(3, 0);
	for (int i = 1; i < s.size(); i++) {
		if (s[i] == 'v' && s[i - 1] == 'v') {
			dp[0]++; dp[2] += dp[1];
		}
		else if (s[i] == 'o') { dp[1] += dp[0]; }
	}

	cout << dp[2] << '\n';
}