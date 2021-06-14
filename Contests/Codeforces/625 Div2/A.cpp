#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> num1(n), num2(n);
	for (auto &x : num1) { cin >> x; }
	for (auto &x : num2) { cin >> x; }

	int toBeat = 1, toDiv = 0;
	for (int i = 0; i < n; i++) {
		if (num1[i] == 0 && num2[i] == 1) { toBeat++; }
		if (num1[i] == 1 && num2[i] == 0) { toDiv++; }
	}

	if (!toDiv) { cout << -1 << endl; }
	else cout << (toBeat+toDiv-1)/toDiv << endl;
}