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
		vector<ll> a(n); for (auto& x : a) { cin >> x; }
		vector<ll> b(n, 1); 

		for (int i = 0; i < n; i++) {
			while (a[i] - b[i] > b[i]) { b[i] *= 2; }
		}

		for (auto& x : b) { cout << x << ' '; }
	}
}