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
		ll k; cin >> k;
		ll numD = 1, cntDigit = 9, pow10 = 1;
		while (k > cntDigit * numD) {
			k -= cntDigit * numD; pow10 *= 10;
			cntDigit *= 10; numD++;
		}

		k--;
		ll num = k / numD + pow10;
		k %= numD;
		string s = to_string(num);
		reverse(s.begin(), s.end());
		while (k--) { s.pop_back(); }

		cout << s.back() << '\n';
	}
}