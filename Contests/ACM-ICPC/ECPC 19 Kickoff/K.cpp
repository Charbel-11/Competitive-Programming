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

	freopen("plants.in", "r", stdin);

	int n; cin >> n;
	vector<int> h(n), g(n);
	for (auto& x : h) { cin >> x; }
	for (auto& x : g) { cin >> x; }

	vector<int> firstInc(n), lastInc(n);
	firstInc[0] = 0;
	lastInc[0] = INT_MAX;

	for (int i = 1; i < n; i++) {
		int first, last;
		if (h[i] >= h[i - 1]) { 
			first = 0;
			if (g[i] >= g[i - 1]) { last = INT_MAX; }
			else { last = (h[i] - h[i - 1]) / (g[i - 1] - g[i]); }
		}
		else {
			if (g[i] <= g[i - 1]) { first = 1; last = 0; }
			else {
				first = (h[i - 1] - h[i] + (g[i] - g[i - 1] - 1)) / (g[i] - g[i - 1]);
				last = INT_MAX;
			}
		}

		firstInc[i] = first;
		lastInc[i] = last;
	}

	int maxFirst = *max_element(firstInc.begin(), firstInc.end());
	int minLast = *min_element(lastInc.begin(), lastInc.end());
	if (maxFirst > minLast) { cout << -1 << '\n'; }
	else { cout << maxFirst << '\n'; }
}