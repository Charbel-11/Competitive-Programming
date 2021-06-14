#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n; cin >> n;

		vector<int> res;

		int cur = n + 1;
		int div = 1;

		while (cur > 0) {	
			int left = div;
			res.push_back(n / cur);
			cur = n / div;
			
			int	add = 1;
			while (cur > 0 && n / cur == res.back()) {
				div += add;
				add *= 2;
				cur = n / div;
			}
			if (cur == 0) { break; }
			int right = div;

			while (left < right) {
				int mid = (left + right) / 2;
				cur = n / mid;
				if (n / cur == res.back()) {
					left = mid + 1;
				}
				else { 
					right = mid; 
				}
			}
			cur = n / left;
		}

		cout << res.size() << endl;
		for (auto &x : res) { cout << x << " "; }
		cout << endl;
	}
}