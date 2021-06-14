#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
const ll mod = 1e9 + 7;
const int maxB = 30;

void addContribution(ll num, vector<vector<int>>& freq) {
	int i = 0;
	vector<int> curFreq(maxB, 0);
	vector<int> used;
	while (num) {
		if (num & 1) { curFreq[i]++; used.push_back(i); }
		num >>= 1; i++;
	}

	for (auto& it : used) {
		for (int j = 0; j < maxB; j++) {
			freq[it][j] += curFreq[j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<ll> x(n); for (auto& xx : x) { cin >> xx; xx %= mod; } 

		vector<vector<int>> freq(maxB, vector<int>(maxB, 0));
		for (auto& num : x) {
			addContribution(num, freq);
		}

		ll aa = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					aa += (x[i] & x[j]) * (x[j] | x[k]);
				}
			}
		}
		cout << aa << '\n';

		ll ans = 0;
		for (int i = 0; i < maxB; i++) {
			if (freq[i][i] == 0) { continue; }
			ll bitToRem = 0;
			for (int j = 0; j < maxB; j++) {
				if (freq[i][j] == 0) { continue; }

				bitToRem |= (1ll << j);
				ll curC = (1ll << i); curC %= mod;
//				curC *= n; curC %= mod;
				curC *= freq[i][i]; curC %= mod;
//				curC *= freq[i][j]; curC %= mod;
//				ans += curC; ans %= mod;

//				cout << i << " " << j << " " << freq[i][i]<<" " << freq[i][j]<<" "<<curC << '\n';

				for (int k = 0; k < n; k++) {
					ll curNum = x[k] | (1ll << j); curNum %= mod;
					curNum *= curC; curNum %= mod;
					ans += curNum; ans %= mod;
				}
			}
			
			for (int k = 0; k < n; k++) {
				ll curNum = x[k] & (~bitToRem); curNum %= mod;
				curNum *= ((1ll << i) % mod); curNum %= mod;
				curNum *= freq[i][i]; curNum %= mod;
				ans += curNum; ans %= mod;
			}
		}
		cout << ans << '\n';
	}
}