#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

void Swap(vector<int>& ans, vector<int>& p, int i, int& left) {
	if (p[i] == i) { left++; }
	if (p[i + 1] == i + 1) { left++; }
	swap(p[i], p[i + 1]); ans.emplace_back(i);
	if (p[i] == i) { left--; }
	if (p[i + 1] == i + 1) { left--; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		int left = 0;
		
		vector<int> p(n);
		for (int i = 0; i < n; i++) {
			cin >> p[i]; p[i]--;
			left += (p[i] != i);
		}

		vector<int> ans; 
		bool odd = false;
		int prev = -1;
		while (left) {
			odd = !odd;

			int start = !odd;
			if (prev > 0) {
				start = prev - 1;
				prev = -1;
			}

			bool done = false;
			for (int i = start; i < n - 1; i += 2) {
				if (p[i] > p[i + 1]) {
					Swap(ans, p, i, left);
					prev = i;
					done = true; break;
				}
			}
			if (done) { continue; }

			int idx = -1;
			for (int i = start + 3; i < n - 1; i += 2) {
				if (p[i] > p[i + 1]) { idx = i; break; }
			}

			for (int i = !odd; i < n - 1; i += 2) {
				if (abs(idx - i) > 1) {
					Swap(ans, p, i, left);
					done = true;
					if (idx != -1){ start = idx + 1; }
					break;
				}
			}
			if (!done) { Swap(ans, p, !odd, left); }
		}

		cout << ans.size() << '\n';
		for (auto& x : ans) { cout << x + 1 << ' '; }
		cout << '\n';
	}
}
