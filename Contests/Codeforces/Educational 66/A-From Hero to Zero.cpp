#include <iostream>
#include <string>

using namespace std;

int main() {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		long long n, k;
		cin >> n >> k;

		long long res = 0;
		while (n != 0) {
			while (n % k == 0) {
				res++;
				n = n / k;
			}

			res += n % k;
			n = n - n % k;
		}

		cout << res << endl;
	}
}