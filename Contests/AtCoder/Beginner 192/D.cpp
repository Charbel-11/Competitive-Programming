#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;

string X; ll M;
ll INF = 1ll << 61;

bool isBigger(ll base) {
	int n = X.size();
	if (log(X[0] - '0') + (n - 1) * log(base) > log(INF)) { return true; }

	ll c = 1;
	for (int i = 1; i < n && c <= M; i++) { c *= base; }
	if (c > M) { return true; }
	ll cur = 0;
	for (int i = 0; i < X.size(); i++) {
		cur += c * (X[i] - '0');
		c /= base;
		if (cur > M) { return true; }
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> X >> M;
	int d = *max_element(X.begin(), X.end()) - '0';

	if (X.size() == 1) {
		if (X[0] - '0' <= M) { cout << 1 << '\n'; }
		else { cout << 0 << '\n'; }
		return 0;
	}
		
	ll l = d, r = INF;
	while (l < r) {
		ll mid = (l + r + 1) >> 1;
		if (isBigger(mid)) { r = mid - 1; }
		else { l = mid; }
	}

	if (r < l) { cout << 0 << '\n'; return 0; }
	cout << (l - d) << '\n';
}