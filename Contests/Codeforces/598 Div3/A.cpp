#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int q; cin >> q;

	while (q--) {
		long long a, b, n, S;
		cin >> a >> b >> n >> S;
		long long temp2 = S / n;
		if (temp2 < a) {
			S -= n * (S / n);
		}
		else {
			S -= a * n;
		}
		if (S <= b) { cout << "YES" << endl; continue; }
		else { cout << "NO" << endl; continue; }
	}
}