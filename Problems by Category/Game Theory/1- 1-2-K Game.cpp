#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int n, k;
		cin >> n >> k;

		bool A = true;
		if (k % 3 != 0) {
			A = n % 3;
		}
		else {
			n %= k + 1;

			if (n == k) { A = true; }
			else {
				A = n % 3;
			}
		}

		if (A) { cout << "Alice" << endl; }
		else { cout << "Bob" << endl; }
	}
}