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

	int t; cin >> t;
	while (t--) {
		int n; ll m; cin >> n >> m;
		vector<int> a(n), b(n);
		for (auto& x : a) { cin >> x; }
		for (auto& x : b) { cin >> x; }
		vector<int> a1, a2;
		for (int i = 0; i < n; i++) {
			if (b[i] == 1) { a1.push_back(a[i]); }
			else { a2.push_back(a[i]); }
		}

		sort(a1.rbegin(), a1.rend());
		sort(a2.rbegin(), a2.rend());

		vector<int> used1; ll cnt = 0;
		ll cur = 0, ans = 1e7;
		for (int i = 0; i < a1.size(); i++) {
			cur += a1[i]; used1.push_back(a1[i]);
			if (cur >= m) { break; }
		}
		int j = -1;
		if (cur < m) {
			for (j = 0; j < a2.size(); j++) {
				cur += a2[j];
				if (cur >= m) { break; }
			}
		}
		if (cur < m) { cout << -1 << '\n'; continue; }

		while (!used1.empty() && cur - used1.back() >= m) {
			cur -= used1.back(); used1.pop_back();
			cnt--; 
		}

		cnt = used1.size() + 2ll * (j + 1);
		ans = min(ans, cnt);

		for (j++; j < a2.size(); j++) {
			cur += a2[j]; cnt += 2;
			while (!used1.empty() && cur - used1.back() >= m) {
				cur -= used1.back(); used1.pop_back(); 
				cnt--;
			}
			ans = min(ans, cnt);
		}

		cout << ans << '\n';
	}
}