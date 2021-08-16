#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> a(n);

		bool OK = false;
		for (auto& x : a) {
			cin >> x;
			if (x == 0) { OK = true; }
		}

		if (!OK) { 
			cout << n + 1 << ' ';
			for (int i = 1; i <= n; i++) { cout << i << ' '; }
			cout << '\n';
			continue;
		}

		int i = n - 1;
		for (; i >= 0; i--) {
			if (a[i] == 0) { break; }
		}

		for (int j = 0; j <= i; j++) {
			cout << j + 1 << ' ';
		}
		cout << n + 1 << ' ';
		for (int j = i + 1; j < n; j++) {
			cout << j + 1 << ' ';
		}
		cout << '\n';
	}
}