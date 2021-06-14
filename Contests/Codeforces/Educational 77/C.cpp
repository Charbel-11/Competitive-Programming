#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int main() {
	int T; cin >> T;

	while (T--) {
		int r, b, k; cin >> r >> b >> k;
		if (r > b) { swap(r, b); }

		int div = (b-gcd(r,b)+r-1) / r;
		if (div >= k) { cout << "REBEL" << endl; }
		else { cout << "OBEY" << endl; }
	}
}