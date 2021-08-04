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
		int n; cin >> n;
		int val1 = n / 3,  val2 = n / 3;
		
		if (val1 + 2 * val2 == n - 1) { val1++; }
		else if (val1 + 2 * val2 == n - 2) { val2++; }

		cout << val1 << " " << val2 << '\n';
	}
}