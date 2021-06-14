#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;

	for (int i = 0; i < n; i++) {
		int res = 0;
		int c, s; cin >> c >> s;

		int d = s / c;
		if (s%c == 0) {
			res += d * d * c;
		}
		else {
			int rem = s % c;
			for (int j = 0; j < rem; j++) {
				res += (d + 1)*(d + 1);
			}
			for (int j = rem; j < c; j++) {
				res += d * d;
			}
		}

		cout << res << endl;
	}

}