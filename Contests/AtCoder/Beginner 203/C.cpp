#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; ll k; cin >> n >> k;
	vector<pair<ll, ll>> friends(n);
	for (auto& p : friends) { cin >> p.first >> p.second; }
	sort(friends.begin(), friends.end());

	ll ans = k;
	for (int i = 0; i < n; i++) {
		if (friends[i].first > ans) { break; }
		ans += friends[i].second;
	}

	cout << ans << '\n';
}
