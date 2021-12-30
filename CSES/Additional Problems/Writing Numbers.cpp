#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pow10[20];

ll numOnesUsingNumsLessThan(ll x) {
	string s = to_string(x);
	ll n = s.size();
	if (n == 1) { return x > 0; }
	
	ll numFirstDigitSmaller = pow10[n - 2] * (n - 1) * (s[0] - '0');
	if (s[0] > '1') { numFirstDigitSmaller += pow10[n - 1]; }

	if (s[0] == '1') { 
		s.erase(0, 1);
		return numFirstDigitSmaller + numOnesUsingNumsLessThan(stoll(s)) + stoll(s) + 1;
	}
	else {
		s.erase(0, 1);
		return numFirstDigitSmaller + numOnesUsingNumsLessThan(stoll(s));
	}	
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	pow10[0] = 1;
	for (int i = 1; i < 20; i++) { pow10[i] = pow10[i - 1] * 10; }

	ll n; cin >> n;
	ll l = 1, r = 1e18;
	while (l < r) {
		ll mid = l + (r - l + 1) / 2;
		if (numOnesUsingNumsLessThan(mid) > n) { r = mid - 1; }
		else { l = mid; }
	}

	cout << l << '\n';
}