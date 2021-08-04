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
		int n, k; cin >> n >> k;
		vector<int> a(n); for (auto& x : a) { cin >> x; }

		vector<int> freq(n + 1, 0);
		for (int i = 0; i < n; i++) { freq[a[i]]++; }

		int cnt = 0;
		for (auto& x : freq) { if (x < k) { cnt += x; } }

		vector<pair<int, int>> v;
		for (int i = 0; i < n; i++) {
			v.push_back({ a[i], i });
		}
		sort(v.begin(), v.end());

		vector<int> ans(n, 0);
		int rem = cnt / k, curCnt = 1;
		for (int i = 0; i < n; i++) {
			int curFreq = freq[v[i].first];
			if (curFreq >= k) {
				int nxtIdx = i + curFreq - 1;

				for (int j = 0; j < k; j++) {
					ans[v[i + j].second] = j + 1;
				}

				i = nxtIdx;
			}
			else {
				if (rem == 0) { continue; }
				ans[v[i].second] = curCnt++;
				if (curCnt == k + 1) { rem--; curCnt = 1; }
			}
		}
	
		for (auto& x : ans) { cout << x << " "; }
		cout << '\n';
	}
}