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
	vector<int> a(n); for (auto& x : a) { cin >> x; }
	vector<int> aS = a; sort(aS.begin(), aS.end());

	int ans = (aS[0] + 1) / 2 + (aS[1] + 1) / 2;

	for (int i = 1; i < n; i++) {
		int c1 = a[i - 1], c2 = a[i];
		if (c1 < c2) { swap(c1, c2); }

		int curAns = 0;
		if (c1 >= c2 * 2) { curAns = (c1 + 1) / 2; }
		else {
			int diff = c1 - c2; curAns = diff;
			c1 -= diff * 2; c2 -= diff;

			curAns += 2 * (c1 / 3); 
			c1 %= 3; c2 %= 3;

			if (c1 == 1) { curAns++; }
			else if (c1 == 2) { curAns += 2; }
		}

		ans = min(ans, curAns);
	}

	for (int i = 1; i < n - 1; i++) {
		int c1 = a[i - 1], c2 = a[i + 1];
		
		int curAns = 1; c1--; c2--;
		curAns += (c1 + 1) / 2 + (c2 + 1) / 2;
		ans = min(ans, curAns);
	}

	cout << ans << '\n';
}