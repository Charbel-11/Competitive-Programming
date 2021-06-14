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
		vector<ll> a(n); for (auto& x : a) { cin >> x; }
		sort(a.rbegin(), a.rend());
		ll A = 0, B = 0;
		for (int i = 0; i < n; i++) {
			if (i % 2 == 0 && a[i] % 2 == 0) { A += a[i]; }
			else if (i % 2 && a[i] % 2) { B += a[i]; }
		}

		if (A > B) { cout << "Alice" << '\n'; }
		else if (A < B) { cout << "Bob" << '\n'; }
		else { cout << "Tie" << '\n'; }
	}
}