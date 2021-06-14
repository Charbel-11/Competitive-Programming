#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int q; cin >> q;

	while (q--) {
		int n; cin >> n;
		vector<int> skills(n);
		for (auto &x : skills) { cin >> x; }
		sort(skills.begin(), skills.end());
		bool two = false;
		for (int i = 0; i < n-1; i++) {
			if (skills[i] == skills[i + 1] - 1) {
				two = true;
				break;
			}
		}

		if (two) {
			cout << 2 << endl; continue;
		}
		cout << 1 << endl;
	}
}