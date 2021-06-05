#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;
const int mod = 1e9 + 7;

int main() {
	int n, k; cin >> n >> k;
	vector<int> dp(k + 2, 0);
	dp[0] = 1;

	for (int i = 0; i < n; i++) {
		int a; cin >> a;
		vector<int> seg(k + 2, 0);	//we can't modify directly the dp array since we want the partial sum of the things we just added
									//not of everything that was there before
		for (int used = k; used >= 0; used--) {
			int L = used + 1;		//+1 since adding nothing doesn't yield a new way
			int R = min(k, used + a);
			if (L > R) { continue; }
			seg[L] += dp[used]; seg[L] %= mod;
			seg[R + 1] -= dp[used]; seg[R + 1] %= mod;
		}
		for (int i = 1; i <= k; i++) {
			seg[i] += seg[i - 1]; seg[i] %= mod;
			dp[i] += seg[i]; dp[i] %= mod;
		}
	}

	cout << (dp[k]+mod)%mod << endl;
}