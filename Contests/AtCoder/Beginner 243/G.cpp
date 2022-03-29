#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;

ll sqrtOf(ll x) {
	ll l = 1, r = min(x, 3000 * 1000 * 1000ull + 10);
	while (l < r) {
		ll mid = l + (r - l + 1) / 2;
		if (mid * mid > x) { r = mid - 1; }
		else { l = mid; }
	}
	return l;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		ll X; cin >> X;
		ll rtX = sqrtOf(X);
		ll rtrtX = sqrtOf(rtX);

		vector<ll> freq(rtrtX + 2, 0);
		for (ll i = rtrtX; i >= 1; i--) {
			ll squareI = i * i;
			freq[i] = rtX - squareI + 1;
		}
		for (ll i = rtrtX; i >= 1; i--) { freq[i] += freq[i + 1]; }

		ll prevRtX = rtrtX, curRtX = sqrtOf(rtrtX);
		vector<ll> curFreq(curRtX + 2, 0);
		while(true){
			for (ll i = curRtX; i >= 1; i--) {
				ll squareI = i * i;
				curFreq[i] = freq[squareI];
			}

			if (curRtX == 1) { break; }

			prevRtX = curRtX; 
			curRtX = sqrtOf(curRtX);

			swap(freq, curFreq);
			for (int i = (int)freq.size() - 2; i >= 1; i--) { freq[i] += freq[i + 1]; }
			curFreq = vector<ll>(curRtX + 2, 0);
		}

		cout << curFreq[1] << '\n';
	}
}