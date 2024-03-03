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

vector<int> manacher(string &s, bool even) {
	int n = s.size();
	vector<int> res(n);
	int l = 0, r = -1;
	for(int i = 0; i < n; i++){
		int k;
		if (i > r) { k = 1; }
		else { k = min(res[l + r - i + even], r - i + even) + 1; }
		while (i + k - even < n && i - k >= 0 && s[i + k - even] == s[i - k]) { k++; }
		res[i] = --k;
		if (i + k - even > r) {
			l = i - k;
			r = i + k - even;
		}
	}
	return move(res);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		string s; cin >> s;
		int n = s.size();
		vector<int> sufMax(n, 1); sufMax.push_back(0);

		vector<int> oddVal = manacher(s, false);
		vector<int> evenVal = manacher(s, true);

		for (int i = n - 1; i >= 0; i--) {
			int lenOdd = oddVal[i] * 2 + 1;
			int befOdd = i - oddVal[i];
			int lenEven = evenVal[i] * 2;
			int befEven = i - evenVal[i];

			sufMax[befOdd] = max(sufMax[befOdd], lenOdd);
			sufMax[befEven] = max(sufMax[befEven], lenEven);
		}

		for (int i = n - 2; i >= 0; i--) {
			sufMax[i] = max(sufMax[i], sufMax[i + 1]);
		}
		for (int i = 1; i < n; i++) {
			sufMax[i] = max(sufMax[i], sufMax[i - 1] - 2);
		}

		int ans = 2;
		for (int i = 0; i < n; i++) {
			int lenOdd = oddVal[i] * 2 + 1;
			int afterOdd = i + oddVal[i] + 1;
			int lenEven = evenVal[i] * 2;
			int afterEven = i + evenVal[i];

			if (afterEven == i) { afterEven++; }

			if (lenOdd == n) { ans = max(ans, n - 1); }
			else{ ans = max(ans, lenOdd + sufMax[afterOdd]); }

			if (lenEven == n) { ans = max(ans, n - 1); }
			else { ans = max(ans, lenEven + sufMax[afterEven]); }
		}

		cout << ans << '\n';
	}
}