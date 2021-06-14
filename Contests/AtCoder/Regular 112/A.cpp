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

	int t; cin >> t;
	while (t--) {
		ll l, r; cin >> l >> r;
	
		if (2 * l > r) { cout << 0 << '\n'; continue; }

		ll k = (r - 2*l) / 2 + 1;
		ll ans = k * 2 * (r - 2*l) + k;
		ans -= (2 * k * (k - 1));
		cout << ans << '\n';

		//2*(r-(2l))+1 + 2*(r-(2l+2))+1 + ... + 2*(r-(2l+2(k-1)))+1
		//=k+2*k*(r-2*l) - 2*(0+2+4+...+2(k-1))=2*2*(1+2+...+K-1)
	}
}