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
		int n, k; cin >> n >> k;
		if (n <= k) { cout << (n + k - 1) / n << '\n'; }
		else if (n % k == 0) { cout << 1 << '\n'; }
		else { cout << 2 << '\n'; }
	}
}