#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

int n;

void solve(int first, int second, int third, int d12, int d23, int d31) {
	bool thirdDone = false;
	int idx = 4;

	int prev = first;
	for (int j = 1; j < d12; j++) {
		if (d31 + d23 == d12 && j == d31) {
			cout << prev << " " << third << '\n';
			prev = third; thirdDone = true;
		}
		else {
			cout << prev << " " << idx << '\n';
			prev = idx++;
		}
	}
	cout << prev << " " << second << '\n';

	if (!thirdDone) {
		int usedIdx = 4;
		for (int j = 1; j < d12; j++) {
			int left13 = d31 - j, left12 = d12 - j;
			if (left13 + left12 == d23) {
				int prev = usedIdx;
				for (int k = 1; k < left13; k++) {
					cout << prev << " " << idx << "\n";
					prev = idx++;
				}
				cout << prev << " " << third << '\n';
				break;
			}
			usedIdx++;
		}
	}

	while (idx <= n) {
		cout << first << " " << idx++ << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int qq; cin >> qq;
	while (qq--) {
		int d12, d23, d31; cin >> n >> d12 >> d23 >> d31;
		vector<int> v = { d12, d23, d31 };
		sort(v.begin(), v.end());

		if (v[0] + v[1] < v[2]) { cout << "NO" << '\n'; continue; }
		if ((v[0] + v[1]) % 2 != v[2] % 2) { cout << "NO" << '\n'; continue; }

		bool OK = true;
		for (int j = 1; j < v[2]; j++) {
			int left13 = v[1] - j, left12 = v[2] - j;
			if (left13 + left12 == v[0]) {
				if (v[2] + 1 + left13 > n) { OK = false; }
			}
		}

		if (!OK) { cout << "NO" << '\n'; continue; }
		cout << "YES" << '\n';
		if (d12 == v[2]) { solve(1, 2, 3, d12, d23, d31); }
		else if (d23 == v[2]) { solve(2, 3, 1, d23, d31, d12); }
		else { solve(3, 1, 2, d31, d12, d23); }
	}
}