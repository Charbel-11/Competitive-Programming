// https://codeforces.com/contest/383/problem/E

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

const int M = (1 << 24);

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> words(n, 0), dp(M, 0);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < 3; j++) {
			words[i] |= (1 << (s[j] - 'a'));
		}
		dp[words[i]]++;
	}

	for (int k = 0; k < 24; k++) {
		for (int mask = M - 1; mask >= 0; mask--) {
			if ((1 << k) & mask) { dp[mask] += dp[mask ^ (1 << k)]; }
		}
	}

	int ans = 0, allOnes = M - 1;
	for (int mask = 0; mask < M; mask++) {
		int curAns = n - dp[allOnes ^ mask];
		ans ^= (curAns * curAns);
	}

	cout << ans << '\n';
}