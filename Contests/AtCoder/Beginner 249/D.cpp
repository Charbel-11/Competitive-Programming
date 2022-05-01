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
	map<int, ll> freq;
	vector<int> A(n); for (auto& x : A) { cin >> x; freq[x]++; }
	sort(A.begin(), A.end());
	A.erase(unique(A.begin(), A.end()), A.end());

	ll ans = 0;
	for (auto& x : A) {
		int d = 1;
		while (d * d < x) {
			if (x % d == 0) {
				ans += freq[x] * freq[d] * freq[x / d] * 2;
			}
			d++;
		}
		if (d * d == x) { ans += freq[x] * freq[d] * freq[d]; }
	}

	cout << ans << '\n';
}