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
		vector<int> a(n); for (auto& x : a) { cin >> x; }
		sort(a.rbegin(), a.rend());

		int A = 0, B = 0;
		for (int i = 0; i < n; i++) {
			if (A > B) { B += a[i]; }
			else { A += a[i]; }
		}

		cout << (A == B ? "YES" : "NO") << '\n';
	}
}