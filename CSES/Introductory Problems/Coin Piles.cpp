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
		int a, b; cin >> a >> b;
		if (a < b) { swap(a, b); }
		if (a > 2 * b || (a + b) % 3) { cout << "NO\n"; continue; }
		cout << "YES\n";
	}
}