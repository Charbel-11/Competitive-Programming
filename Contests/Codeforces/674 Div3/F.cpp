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
const ll mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	string s; cin >> s;
	vector<ll> dp(3, 0);

	ll powerQ = 1;
	for (int i = 0; i < n; i++) {
		vector<ll> newDP = dp;
		
		if (s[i] == '?') {
			for (int i = 0; i < 3; i++) {
				newDP[i] *= 3; newDP[i] %= mod;
			}
			newDP[0] += powerQ; newDP[0] %= mod;
			newDP[1] += dp[0]; newDP[1] %= mod;
			newDP[2] += dp[1]; newDP[2] %= mod;

			powerQ *= 3; powerQ %= mod; 
		}
		else if (s[i] == 'a') { newDP[0] += powerQ; newDP[0] %= mod; }
		else if (s[i] == 'b') { newDP[1] += dp[0]; newDP[1] %= mod; }
		else if (s[i] == 'c') { newDP[2] += dp[1]; newDP[2] %= mod; }

		swap(dp, newDP);
	}

	cout << dp[2] << '\n';
}