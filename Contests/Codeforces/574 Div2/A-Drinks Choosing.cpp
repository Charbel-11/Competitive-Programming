#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> drinkFreq(k, 0);

	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		drinkFreq[temp - 1]++;
	}

	int sets = (n + 1) / 2;
	int res = 0;

	for (int i = 0; i < k; i++) {
		n -= 2 * (drinkFreq[i] / 2);
		sets -= drinkFreq[i] / 2;
		res += 2 * (drinkFreq[i] / 2);
		drinkFreq[i] %= 2;
	}
	if (sets > n) {
		res += n;
	}
	else {
		res += sets;
	}

	cout << res << endl;
}