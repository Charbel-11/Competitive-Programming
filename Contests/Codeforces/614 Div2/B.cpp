#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
	int n; cin >> n;

	double ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += (1 / (double)i);
	}

	cout << setprecision(5) << ans << endl;
}