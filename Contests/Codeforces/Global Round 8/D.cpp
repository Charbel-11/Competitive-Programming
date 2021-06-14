#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> base;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	base.resize(n);
	for (auto &x : base) { cin >> x; }
	
	vector<int> bits(21, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 21; j++) {
			if ((base[i] >> j) & 1) { bits[j]++; }
		}
	}

	ll res = 0, cur = 0;
	bool repeat = 1;
	while (repeat) {
		repeat = 0; cur = 0;
		for (int j = 20; j >= 0; j--) {
			if (bits[j]) { bits[j]--;  cur += (1 << j); repeat = 1; }
		}
		res += cur * cur;
	}

	cout << res << '\n';
}