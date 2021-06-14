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
		ll n; cin >> n;
		ll pow2 = 0;
		while (n % 2 == 0) { pow2++; n >>= 1; }

		if (pow2 == 0) { cout << "Odd" << '\n'; }
		else if (pow2 > 1) { cout << "Even" << '\n'; }
		else {
			cout << "Same" << '\n';
		}
	}
}