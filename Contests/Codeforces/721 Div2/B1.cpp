#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		string s; cin >> s;
		int zeros = 0;
		for (auto& c : s) { zeros += (c == '0'); }

		if ((zeros % 2 == 0) || zeros == 1) { cout << "BOB" << '\n'; }
		else { cout << "ALICE" << '\n'; }
	}
}
