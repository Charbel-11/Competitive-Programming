#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> b(n);
	for (auto &x : b) { cin >> x; }
	vector<int> a(n);
	a[0] = b[0];

	int x = 0;
	for (int i = 1; i < n; i++) {
		x = max(x, a[i-1]);
		a[i] = b[i] + x;
	}

	for (auto &x : a) { cout << x << " "; }
	cout << endl;
}