#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> a(n), t(n);
	for (auto &x : a) { cin >> x; }
	for (auto &x : t) { cin >> x; }

	vector<pair<ll, ll>> category(n);
	for (int i = 0; i < n; i++) {
		category[i] = { a[i], t[i] };
	}

	sort(category.begin(), category.end());
	category.push_back({ LLONG_MAX, 0 });

	ll ans = 0;
	multiset<ll> carry; ll curSum = 0;
	for (int i = 1; i <= n; i++) {
		if (category[i].first == category[i - 1].first) {
			carry.insert(category[i - 1].second); curSum += category[i - 1].second;
			if (category[i].first != category[i + 1].first) {
				goto L;
			}
		}
		else {
			if (category[i].first > category[i - 1].first + 1) {
				for (int k = category[i - 1].first + 1; k < category[i].first && !carry.empty(); k++) {
					ans += curSum;
					curSum -= *(--carry.end());
					carry.erase(--carry.end());
				}
			}

			if (i == n) { break; }

			ans += curSum;
			if (category[i].first != category[i+1].first) {
			L:	carry.insert(category[i].second);
				curSum += category[i].second;
				curSum -= *(--carry.end());
				carry.erase(--carry.end());
			}
		}
	}

	cout << ans << endl;
}