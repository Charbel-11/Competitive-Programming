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

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
long long lcm(int a, int b) { return (long long)(a / gcd(a, b)) * b; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int a, b, q; cin >> a >> b >> q;
		if (a > b) { swap(a, b); }
		ll mult = lcm(a, b);
		while (q--) {
			ll ans = 0;
			ll l, r; cin >> l >> r; ll iR = r, iL = l;

			ll firstLCM = (ll)mult * (l / mult);
			ll equal = firstLCM + b - 1;
			firstLCM += mult;

			if (equal >= l) { ans += (min(r, equal) - l + 1); l = equal + 1; }

			if (l <= r) {
				ll repeatedLCM = (r - firstLCM + 1) / mult;	
				ans += repeatedLCM * b;
				l = firstLCM + (repeatedLCM*mult);
				if (l <= r) {
					for (ll i = l; i <= r; i++) {
						if (i%mult == 0) { ans += min((ll)b, r-i+1); break; }
					}
				}
			}

/*			int brute = 0;
			for (int i = iL; i <= iR; i++) {
				if ((i%b) % a != (i%a) % b) { brute++; }
			}
			cout << "B" << brute << endl;
			*/
			cout << (iR - iL + 1ll - ans) << " ";
		}
		cout << endl;
	}
}