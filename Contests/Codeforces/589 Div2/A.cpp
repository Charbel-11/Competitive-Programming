#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

bool checkDigits(int n) {
	set<int> S;

	while (n > 0) {
		int cur = n % 10;
		if (S.count(cur) != 0) {
			return false;
		}
		S.insert(cur);
		n /= 10;
	}
	return true;
}

int main() {
	int l, r; cin >> l >> r;

	for (int i = l; i <= r; i++) {
		if (checkDigits(i)) {
			cout << i << endl;
			return 0;
		}
	}

	cout << -1 << endl;
}