#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;

	if (n % 2 == 0) { cout << "NO" << endl; return 0; }

	cout << "YES" << endl;

	vector<int> answ(2 * n);

	int cur = 1;
	for (int i = 0; i < n; i++) {
		if (i % 2) {
			answ[i] = cur; answ[i + n] = cur + 1;
		}
		else {
			answ[i] = cur + 1; answ[i + n] = cur;
		}
		cur+=2;
	}

	for (int i = 0; i < 2 * n; i++) {
		cout << answ[i] << " ";
	}
}