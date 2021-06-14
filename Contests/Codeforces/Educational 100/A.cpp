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
		ll a, b, c; cin >> a >> b >> c;
		ll s = a + b + c;
		if (s * 7 % 9) { cout << "NO\n"; continue; }
		ll k = s * 7 / 9; k /= 7;
		if (a<k||b<k||c<k){ cout << "NO\n"; continue; }
		cout << "YES\n";
	}
}