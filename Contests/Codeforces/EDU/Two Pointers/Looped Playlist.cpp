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

	int n; ll p; cin >> n >> p;
	ll S = 0; vector<ll> a(n);
	for (auto& x : a) { cin >> x; S += x; }

	int start = 0; ll cnt = 0;
	cnt += (p / S) * n; p %= S;

	if (p > 0) {
		int minCnt = n + 1, r = -1;
		ll curPos = 0;
		for (int l = 0; l < n; l++) {
			while (curPos < p) {
				r++; if (r == n) { r = 0; }
				curPos += a[r];
			}

			int range = r - l + 1;
			if (r < l) { range = n - (l - r - 1); }
			if (range < minCnt) { minCnt = range; start = l; }

			curPos -= a[l];
		}

		cnt += minCnt;
	}

	cout << start + 1 << ' ' << cnt << '\n';
}