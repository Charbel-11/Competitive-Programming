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
		ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;

		ll dy = y2 - y1, dx = x2 - x1;
		cout << dx * dy + 1 << endl;
	}
}