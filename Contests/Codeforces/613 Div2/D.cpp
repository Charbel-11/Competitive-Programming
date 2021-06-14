#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> a;
int n;

int findMin(int i, int j, int bit) {
	if (j < i || bit < 0) { return 0; }
	
	bool b = (a[i] >> bit & 1);
	int l = i + 1; bool same = true;
	for (; l <= j; l++) {
		if ((a[l] >> bit & 1) != b) { same = false; break; }
	}

	if (same) { return findMin(i, j, bit - 1); }

	int cut = i; l = i;
	for (; l <= j; l++) {
		if ((a[l] >> bit) & 1) { cut = l; break; }
	}

	return (1<<bit) + min(findMin(i, cut-1, bit-1), findMin(cut, j, bit-1));
}

int main() {
	cin >> n;
	a.resize(n);
	for (auto &x : a) { cin >> x; }

	sort(a.begin(), a.end());
	cout << findMin(0, n - 1, 29) << endl;
}