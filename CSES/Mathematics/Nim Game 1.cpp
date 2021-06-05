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
		int n, x = 0; cin >> n;
		for (int i = 0; i < n; i++) { int cur; cin >> cur; x ^= cur; }
		if (x) { cout << "first" << '\n'; }
		else { cout << "second" << '\n'; }
	}
}