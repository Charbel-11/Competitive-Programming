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
		ll x, y, a, b; cin >>x>>y>> a >> b;
		if (2ll * a <= b) { cout << (x+y)*a << endl; continue; }
		ll init = min(x, y);
		x -= init; y -= init;
		cout << (init*b) + (x + y)*a << endl;
	}
}