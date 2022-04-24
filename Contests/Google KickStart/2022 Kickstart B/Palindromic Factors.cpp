#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool isPalindrome(ll x) {
	string s = to_string(x);
	int n = s.size();
	for (int i = 0; i < n / 2; i++) {
		if (s[i] != s[n - i - 1]) { return false; }
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	for (int qq = 1; qq <= t; qq++) {
		ll A; cin >> A;

		ll ans = 1, d = 2;
		while (d * d <= A) {
			if (A % d == 0) {
				if (isPalindrome(d)) { ans++; }
				if (d * d < A && isPalindrome(A / d)) { ans++; }
			}
			d++;
		}

		if (A != 1) { ans += isPalindrome(A); }

		cout << "Case #" << qq << ": " << ans << '\n';
	}
}
