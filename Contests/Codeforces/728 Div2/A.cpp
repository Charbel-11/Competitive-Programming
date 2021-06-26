#include <iostream>
#include <string>
#include <map>
#include <set>
#include <numeric>
#include <vector>
#include <cmath>
#include <algorithm>
#define deb(x) cout << #x << " " << x 
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<int> v(n);
		iota(v.begin(), v.end(), 1);

		for (int i = 0; i < n - 1; i += 2) {
			swap(v[i], v[i + 1]);
		}
		if (n % 2) { swap(v[n - 2], v[n - 1]); }

		for (auto& x : v) { cout << x << " "; }
		cout << '\n';
	}
}