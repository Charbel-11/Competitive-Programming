#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> A(n); for (auto& x : A) { cin >> x; }

	vector<ll> dp(n + 1, 0); dp[0] = 1;
	ll curMaxAns = 0, curMinAns = 0;

	stack<pair<ll, ll>> sMax, sMin;
	for (int i = 0; i < n; i++) {
		ll dpSumForCurMax = dp[i];
		while (!sMax.empty() && sMax.top().first < A[i]) {
			ll prevMax = sMax.top().first, prevDPSum = sMax.top().second;
			dpSumForCurMax += prevDPSum; dpSumForCurMax %= mod;
			curMaxAns -= prevDPSum * prevMax; curMaxAns %= mod;
			sMax.pop();
		}
		curMaxAns += (dpSumForCurMax * A[i]) % mod; curMaxAns %= mod;
		sMax.push({ A[i], dpSumForCurMax });

		ll dpSumForCurMin = dp[i];
		while (!sMin.empty() && sMin.top().first > A[i]) {
			ll prevMin = sMin.top().first, prevDPSum = sMin.top().second;
			dpSumForCurMin += prevDPSum; dpSumForCurMin %= mod;
			curMinAns -= prevDPSum * prevMin; curMinAns %= mod;
			sMin.pop();
		}
		curMinAns += (dpSumForCurMin * A[i]) % mod; curMinAns %= mod;
		sMin.push({ A[i], dpSumForCurMin });

		dp[i + 1] = curMaxAns - curMinAns; dp[i + 1] %= mod;
		if (dp[i + 1] < 0) { dp[i + 1] += mod; }
	}

	cout << dp[n] << '\n';
}