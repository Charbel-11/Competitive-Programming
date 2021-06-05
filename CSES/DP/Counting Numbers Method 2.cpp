#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

//The idea here is to avoid dealing with leading zeros
ll countUpTo(ll num) {
	if (num <= 10) { return num; }

	ll ans = 0;
	string s = to_string(num);

	//Count numbers with 1,2,...,s.size()-1 digits with no constraints
	vector<ll> curDP(10, 0), prevDP(10, 1);
	ans = 9; prevDP[0] = 0;
	for (int i = 1; i < s.size() - 1; i++) {
		for (int j = 0; j < 10; j++) {
			curDP[j] = 0;
			for (int k = 0; k < 10; k++) {
				if (j == k) { continue; }
				curDP[j] += prevDP[k];
			}
		}
		for (int j = 0; j < 10; j++) { ans += curDP[j]; }
		swap(curDP, prevDP);
	}

	//Count digits of size s.size()
	vector<vector<ll>> dp1(10, vector<ll>(2, 0)), dp2(10, vector<ll>(2, 0));
	for (int i = 1; i < s[0] - '0'; i++) { dp2[i][0] = 1; }
	dp2[s[0] - '0'][1] = 1;
	for(int i = 1; i < s.size(); i++){
		for (int j = 0; j < 10; j++) {
			dp1[j][0] = dp1[j][1] = 0;
			for (int k = 0; k < 10; k++) {
				if (j == k) { continue; }
				dp1[j][0] += dp2[k][0];
				if (j < s[i] - '0') { dp1[j][0] += dp2[k][1]; }
			}
		}
		if (s[i] != s[i - 1]) dp1[s[i] - '0'][1] += dp2[s[i - 1] - '0'][1];

		swap(dp1, dp2);
	}

	for (int i = 0; i < 10; i++) { ans += dp2[i][0] + dp2[i][1]; }

	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll a, b; cin >> a >> b;
	cout << countUpTo(b) - countUpTo(a - 1) << '\n';
}