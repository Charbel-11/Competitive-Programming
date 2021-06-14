#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
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
		for (auto &x : a) { cin >> x; }
		sort(a.begin(), a.end());
		int even = 0, odd = 0; bool cons = false;
		for (int i = 0; i < n; i++) {
			even += !(a[i] % 2);
			odd += a[i] % 2;
			if (i && a[i] == a[i - 1] + 1) { cons = true; }
		}

		if (even % 2 != odd % 2) { cout << "NO" << endl; }
		else if (even % 2 && odd % 2 && !cons) { cout << "NO" << endl; }
		else { cout << "YES" << endl; }
	}
}