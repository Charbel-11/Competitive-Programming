#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int q;
	cin >> q;

	for (int i = 0; i < q; i++) {
		long long n;
		cin >> n;

		long long res = 0;

		while (true) {
			if (n == 1) {
				cout << res << endl;
				break;
			}

			if (n % 2 == 0) {
				n = n / 2;
			}
			else if (n % 3 == 0) {
				n = (n/3) * 2;
			}
			else if (n % 5 == 0) {
				n = (n / 5) * 4;
			}
			else if (n != 1) {
				cout << -1 << endl;
				break;
			}
		}
	}
}