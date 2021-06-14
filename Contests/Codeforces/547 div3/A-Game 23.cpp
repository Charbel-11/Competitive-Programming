#include <iostream>
#include <string>

using namespace std;

int main() {
	int n, m;
	cin >> n >> m;

	if (m%n != 0) {
		cout << -1 << endl;
		return 0;
	}

	m = m / n;

	int res = 0;
	while (m % 2 == 0) {
		res++;
		m = m / 2;
	}
	while (m % 3 == 0) {
		res++;
		m = m / 3;
	}

	if (m != 1) {
		cout << -1 << endl;
	}
	else {
		cout << res << endl;
	}
}