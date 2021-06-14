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

	int n, k; cin >> n >> k;
	vector<int> a(n), freq(n, 0);
	for (auto& x : a) { cin >> x; freq[x]++; }

	ll ans = 0;
	for (int i = 0; i < n; i++) {
		if (freq[i] < k) { 
			ans += (ll)(k - freq[i]) * i; 
			k = freq[i]; 
		}
	}
	cout << ans << '\n';
}