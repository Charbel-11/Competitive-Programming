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
		ll n, m, x; cin >> n >> m >> x;
		x--;
		ll row = x % n, col = x / n;
		cout << (row * m + col + 1) << '\n';
	}
}