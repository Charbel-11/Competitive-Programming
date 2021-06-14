#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int q; cin >> q;

	for (int z = 0; z < q; z++) {
		int n; cin >> n;

		vector<int> powers(12, 0);
		for (int i = 0; i < n; i++) {
			int num; cin >> num;
			if (num >= 1 << 12) { continue; }
			else {
				int res = 0;
				while (num % 2 == 0) { num /= 2; res++; }
				powers[res]++;
			}
		}

		for (int i = 0; i < 11; i++) {
			powers[i+1] += powers[i]/2;
		}
		if (powers[11] > 0) { cout << "YES" << endl; }
		else { cout << "NO" << endl; }
	}
}