#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int n, k;
vector<int> stalls;

bool check(int mid) {
	int cur = 1, lastIdx = 0;
	for (int i = 1; i < n; i++) {
		if (stalls[i] - stalls[lastIdx] >= mid) { cur++; lastIdx = i; }
	}
	return cur >= k;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	stalls.resize(n);
	for (auto& x : stalls) { cin >> x; }

	int l = 0, r = 1e9;
	while (l < r) {
		int mid = (l + r + 1) / 2;
		if (check(mid)) { l = mid; }
		else { r = mid - 1; }
	}

	cout << l << '\n';
}