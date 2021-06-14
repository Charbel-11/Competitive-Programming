#include <iostream>
#include <string>

using namespace std;


int main() {
	int n, x, y;
	string num;
	cin >> n >> x >> y >> num;

	int res = 0;

	for (int i = n - 1; i > n - x - 1; i--) {
		if (i != n - y - 1 && num[i] == '1') {
			res++;
		}
		else if (i == n - y - 1 && num[i] == '0') {
			res++;
		}
	}

	cout << res << endl;
}