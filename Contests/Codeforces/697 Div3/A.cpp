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
		ll n; cin >> n;
		while (n > 1 && n % 2 == 0) { n >>= 1; }
		cout << (n != 1 ? "YES" : "NO") << '\n';
	}
}