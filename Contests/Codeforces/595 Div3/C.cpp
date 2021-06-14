#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int q; cin >> q;
	while (q--) {
		ll n; cin >> n;

		vector<ll> base3(40, 0);
		int i = 0;
		while (n > 0) {
			base3[i] = n % 3;
			n /= 3; i++;
		}

		int last2 = -1;
		for (int i = 0; i < 39; i++) {
			if (base3[i] > 1) { last2 = i; }
		}

		if (last2 != -1) {
			while (base3[last2]) { last2++; }
			base3[last2] = 1; last2--;
			while (last2 != -1) {
				base3[last2] = 0;
				last2--;
			}
		}

		ll res = 0, pow3 = 1;
		for (int i = 0; i < 40; i++) {
			if (base3[i]) { base3[i] = 1; }
			res += base3[i] * pow3;
			pow3 *= 3;
		}

		cout << res << endl;
		
	}
}