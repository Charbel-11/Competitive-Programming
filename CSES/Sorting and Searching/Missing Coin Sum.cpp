#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> x(n); for (auto& xx : x) { cin >> xx; }
	sort(x.begin(), x.end());

	ll cur = 1;
	for (int i = 0; i < n; i++) {
		if (cur < x[i]) { break; }
		cur += x[i];
	}

	cout << cur << '\n';
}