#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll mod = 998244353;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<int> a(n), b(m);
	for (auto &x : a) { cin >> x; }
	for (auto &x : b) { cin >> x; }

	map<int, int> freq;
	int sufMin = a.back(); freq[sufMin]++;
	for (int i = n - 2; i >= 0; i--) {
		sufMin = min(sufMin, a[i]);
		freq[sufMin]++;
	}

	if (freq.begin()->first != b[0]) { cout << 0 << '\n'; return 0; }
	ll res = 1;
	for (int i = 1; i < m; i++) { res *= freq[b[i]]; res %= mod; }
	cout << res << '\n';
}