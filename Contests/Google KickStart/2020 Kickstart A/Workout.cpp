#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
vector<int> minutes;
int N, K;

bool check(int diff) {
	int left = K;
	for (int i = 1; i < N; i++) {
		int curDiff = minutes[i] - minutes[i - 1];
		left -= ((curDiff + diff - 1) / diff) - 1;
	}
	return left >= 0;
}

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		cin >> N >> K;
		minutes.clear(); minutes.resize(N);
		for (auto &x : minutes) { cin >> x; }

		int l = 1, r = 1;
		for (int i = 1; i < N; i++) {
			r = max(r, minutes[i] - minutes[i - 1]);
		}

		while (l < r) {
			int mid = l + (r - l) / 2;
			bool b = check(mid);
			if (b) { r = mid; }
			else { l = mid + 1; }
		}

		cout << "Case #" << z + 1 << ": " << l << endl;
	}
}