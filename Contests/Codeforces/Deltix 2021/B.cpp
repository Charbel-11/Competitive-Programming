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
		int n; cin >> n;
		vector<int> a(n); for (auto& x : a) { cin >> x; }

		vector<int> evenIdx, oddIdx;
		int even = 0, odd = 0;
		for(int i = 0; i < n; i++){
			if (a[i] % 2 == 1) { odd++; oddIdx.push_back(i); }
			else { even++; evenIdx.push_back(i); }
		}

		if (abs(even - odd) > 1) { cout << -1 << '\n'; continue; }

		ll ans = (ll)n * n;

		//start e
		if (even == (n + 1) / 2) {
			ll curAns = 0; int curIdx = 0;
			for (int i = 0; i < n; i += 2) {
				curAns += abs(i - evenIdx[curIdx]);
				curIdx++;
			}
			ans = min(ans, curAns);
		}

		//start o
		if (odd == (n + 1) / 2) {
			ll curAns = 0; int curIdx = 0;
			for (int i = 0; i < n; i += 2) {
				curAns += abs(i - oddIdx[curIdx]);
				curIdx++;
			}
			ans = min(ans, curAns);
		}

		cout << ans << '\n';
	}
}