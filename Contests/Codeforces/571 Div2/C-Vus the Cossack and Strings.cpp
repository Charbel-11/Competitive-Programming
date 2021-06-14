#include <string>
#include <iostream>

using namespace std;

int main() {
	string a, b;
	cin >> a >> b;

	int res = 0;

	bool evenSwitch = true;
	for (int i = 0; i < b.size() - 1; i++) {
		if (b[i] != b[i + 1]) {
			evenSwitch = !evenSwitch;				//Number of differences when shifting mod 2
		}
	}

	int curDiff = 0;
	for (int i = 0; i < b.size(); i++) {
		if (b[i] != a[i]) {
			curDiff++;
		}
	}

	if (curDiff % 2 == 0) { res++; }

	for (int i = 1; i + b.size() <= a.size(); i++) {
		curDiff += !evenSwitch;

		if (a[i - 1] != b[0]) { curDiff--; }
		if (a[i + b.size() - 1] != b[b.size() - 1]) { curDiff++; }

		if (curDiff % 2 == 0) { res++; }
	}

	cout << res << endl;
}