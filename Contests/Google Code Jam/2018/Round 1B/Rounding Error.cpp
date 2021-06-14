#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int T; cin >> T;

	for (int z = 1; z <= T; z++) {
		int N, L; cin >> N >> L;
		multiset<int> offset;

		int ans = 0, cap = (N + 1) / 2, rem = N;
		for (int i = 0; i < L; i++) {
			int c; cin >> c; rem -= c;
			ans += (100 * c) / N;

			int mod = (100*c) % N;
			if (mod >= cap) { ans++; }
			else { offset.insert(cap - mod); }
		}
		offset.insert(cap);

		int i = 0;
		for (int i = 1; i <= rem; i++) {
			int cur = (100 * i) % N;
			while (i <= rem) {
				auto it = offset.upper_bound(cur);
				if (it == offset.begin()) { break; }
				it--; ans++;
				ans += (100 * i) / N;
				rem -= i;
				int newMod = cap + (cur - *it); newMod %= N;
				if (*it != cap) { offset.erase(it); }
				offset.insert(newMod);
			}
		}		
		ans += (rem * 100) / N;

		cout << "Case #" << z << ": " << ans << endl;
	}
}