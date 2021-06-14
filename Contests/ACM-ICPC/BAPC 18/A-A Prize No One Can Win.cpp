
#include <iostream>
#include <algorithm>
using namespace std;

int n, x;

int calc(int * p) {
	if (n == 1) { return 1; }
	if (p[0] > x) { return 1; }
	int ret = 1;
	int i = 0;
	while (p[i] + p[i + 1] <= x) {
		ret++;
		i++;
		if (i == n - 1) { break; }
	}
	return ret;
}

int main() {
	cin >> n >> x;
	int * p = new int[n];
	for (int i = 0; i < n; i++) { cin >> p[i]; }
	sort(p, p + n);
	cout << calc(p) << endl;

	return 0;
}