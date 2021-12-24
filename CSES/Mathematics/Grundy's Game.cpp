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

	vector<int> GN(1300, 0);
	for (int i = 3; i < 1300; i++) {
		vector<bool> seen(650, 0);
		for (int j = 1; j < (i + 1) / 2; j++) {
			int curGN = GN[j] ^ GN[i - j];
			if (curGN < 650) { seen[curGN] = true; }
		}
		GN[i] = find(seen.begin(), seen.end(), false) - seen.begin();
	}

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		if (n >= 1300 || GN[n] > 0) { cout << "first" << '\n'; }
		else { cout << "second" << '\n'; }
	}
}