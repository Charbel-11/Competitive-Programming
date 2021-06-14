#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		set<int> rem;
		for (int i = 1; i < 205; i++) { rem.insert(i); }

		int n, x; cin >> n >> x;
		while (n--) {
			int cur; cin >> cur;
			rem.erase(cur);
		}
		while (x--) {
			rem.erase(rem.begin());
		}

		cout << *rem.begin() - 1 << endl;
	}
}