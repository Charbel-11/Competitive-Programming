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

	freopen("equal.in", "r", stdin);

	int t; cin >> t;
	while (t--) {
		int a, b, c; cin >> a >> b >> c;
		if (a == b || a == c || b == c) { cout << "YES" << '\n'; }
		else { cout << "NO" << '\n'; }
	}
}