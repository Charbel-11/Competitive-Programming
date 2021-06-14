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

	int t; cin >> t;

	while (t--) {
		ll a, b; cin >> a >> b;
		int op = 0;
		if (a > b) {
			while (a > b) { 
				if (a % 8 == 0 && a / 8 >= b) { a /= 8; op++; }
				else if (a % 4 == 0 && a / 4 >= b) { a /= 4; op++; }
				else if (a % 2 == 0 && a / 2 >= b) { a /= 2; op++; }
				else { break; }
			}
		}
		else {
			while (a < b) {
				if (a * 8 <= b) { a *= 8; op++; }
				else if (a * 4 <= b) { a *= 4; op++; }
				else if (a * 2 <= b) { a *= 2; op++; }
				else { break; }
			}
		}

		cout << (a == b ? op : -1) << '\n';
	}
}