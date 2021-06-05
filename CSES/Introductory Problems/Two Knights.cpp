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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ll n; cin >> n;
	
	for (ll k = 1; k <= n; k++) {
		ll tot = k * k;
		ll res = tot * (tot - 1) / 2;
		ll rem = 0;

		if (k > 4) { rem += (k - 4)*(k - 4) * 8; }	//inside square
		if (k > 3) {
			rem += (k - 4) * 4 * 6;	//second square without corners
			rem += 4 * 4;			//corners of second square
		}

		//First square
		if (k > 2) { rem += 8; }	//corners
		if (k == 3) { rem += 8; }
		else if (k > 3) { rem += 8 * 3; }

		if (k > 4) { rem += (k - 4) * 4 * 4; }

		res -= rem / 2;
		cout << res << '\n';
	}
}