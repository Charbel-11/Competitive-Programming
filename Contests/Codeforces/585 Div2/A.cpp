#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int a1, a2, k1, k2, n;
	cin >> a1 >> a2 >> k1 >> k2 >> n;

	int mini = 0, maxi = 0;
	int stay = a1 * (k1 - 1) + a2 * (k2 - 1);
	if (stay < n) { mini = min(n - stay, a1 + a2); }

	if (k1 > k2) {
		maxi += min(a2, n / k2);
		n -= k2 * min(a2, (n / k2));

		maxi += min(a1, n / k1);
	}
	else {
		maxi += min(a1, n / k1);
		n -= k1 * min(a1, (n / k1));

		maxi += min(a2, n / k2);
	}

	cout << mini << " " << maxi << endl;
}