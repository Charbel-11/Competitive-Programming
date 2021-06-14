#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<int> a(n), b(n);
		for (auto &x : a) { cin >> x; }
		for (auto &x : b) { cin >> x; }
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());

		for (int i = 0; i < n; i++) {
			cout << a[i] << " ";
		}cout << endl;
		for (int i = 0; i < n; i++) {
			cout << b[i] << " ";
		}cout << endl;
	}
}