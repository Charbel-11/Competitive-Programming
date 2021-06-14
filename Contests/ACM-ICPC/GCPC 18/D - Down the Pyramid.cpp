#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

vector<ll> v;

//First number set uniquely determines all other numbers
//When we increase it by 1, all odd numbers decrease and even number increase by 1

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	int n; cin >> n; v.resize(n);
	for (auto &x : v) { cin >> x; }
	ll ma = 1ll << 60, mi = 0, c = 0;

	for (int i = 0; i <= n; i++) {
		if (i % 2 == 0) { mi = max(mi, -c); }
		else { ma = min(ma, c); }
		if (i < n) { c = v[i] - c; }
	}
	cout << max(0ll, ma - mi + 1) << endl;
}