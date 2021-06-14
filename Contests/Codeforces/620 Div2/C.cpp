#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n, temp; cin >> n >> temp;
		int curTime = 0, spare = 0;
		int possTempLow = temp, possTempHigh = temp;	//can be anthg between those

		bool OK = true;
		for (int i = 0; i < n; i++) {
			int time, low, high; cin >> time >> low >> high;

			spare = time - curTime; curTime = time;
			possTempLow -= spare;
			possTempHigh += spare;

			if (low > possTempHigh || high < possTempLow) {
				OK = false; continue;
			}

			possTempLow = max(low, possTempLow);
			possTempHigh = min(high, possTempHigh);
		}

		cout << (OK ? "YES" : "NO") << endl;
	}
}