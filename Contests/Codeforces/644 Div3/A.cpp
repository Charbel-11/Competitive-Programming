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
		if (a > b) { swap(a, b); }
		int c1 = 2 * a;
		if (b > 2 * a) { cout << b * b << endl; continue; }
		cout << c1*c1 << endl;
	}
}