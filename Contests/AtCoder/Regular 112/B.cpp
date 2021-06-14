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

	ll B, C; cin >> B >> C;
	ll twos = C / 2;

	bool add1 = false, add2 = false;
	ll smallestB = B - twos, ans = 0;
	if (smallestB == 0 && B == 0) { cout << 1 << '\n'; return 0; }
	else if (smallestB == 0) {
		ans = (B - smallestB) * 2 + 1;
		add1 = true;
	}
	else if (B == 0) {
		ans = (B - smallestB) * 2 + 1;
		if (C % 2 == 0) { ans--; }
	}
	else if ((smallestB < 0 && B < 0) || (smallestB > 0 && B > 0)) {
		ans = (B - smallestB + 1) * 2;
		if (C % 2 == 0) { ans--; }
		if (smallestB < 0 && B < 0) { add2 = true; }
		else { add1 = true; }
	}
	else {
		ans = 2 * max(abs(smallestB), abs(B)) + 1;
		if (B >= abs(smallestB)) { add1 = true; }
		else {
			C--; twos = C / 2; B = -B;
			ll nB = B - twos;
			ll diff = smallestB - nB;
			ans += diff * 2;
			if (C % 2 == 0) { ans--; }
		}
	}

	if (C == 1) { add1 = add2 = false; }
	if (add1) {
		C--; twos = C / 2; B = -B;
		smallestB = B - twos;
		ans += (B - smallestB) * 2;
		if (C % 2 == 0) { ans--; }
	}
	else if (add2) {
		C--; twos = C / 2; B = -B;
		smallestB = max(B - twos, 0ll);
		ans += (B - smallestB) * 2;
		if (smallestB == 0 || C % 2 == 0) { ans--; }
	}

	cout << ans << '\n';
}