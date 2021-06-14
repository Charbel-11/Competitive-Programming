#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<long long> sweets(n);
	for (auto &x : sweets) { cin >> x; }

	sort(sweets.begin(), sweets.end());

	vector<long long> add(m, 0);
	long long prevRes = 0;
	for (int i = 0; i < n; i++) {
		long long res = prevRes + sweets[i] + add[i%m];
		add[i%m] += sweets[i];
		cout << res << " ";
		prevRes = res;
	}
}