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
		int c, d; cin >> c >> d;
		if (c == d && c == 0) { cout << 0 << '\n'; }
		else if (c == d) { cout << 1 << '\n'; }
		else {
			int dif = abs(c - d);
			if (dif % 2) { cout << -1 << '\n'; }
			else { cout << 2 << '\n'; }
		}
	}
}