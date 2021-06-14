#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	vector<int> perfectSquares;
	for (int i = 0; i < 3163; i++)
		perfectSquares.push_back(i*i);

	vector<int> seen(4e7 + 5, 0);
	vector<int> used; int shift = 2e7+1;

	for (int qq = 1; qq <= t; qq++) {
		int ans = 0;

		for (auto &it : used) { seen[it] = 0; }
		used.clear();

		seen[shift] = 1; used.push_back(shift);
		int n; cin >> n;
		int cur = 0, minFound = 0;
		for (int i = 0; i < n; i++) {
			int tmp; cin >> tmp; cur += tmp; 
			for (auto &x : perfectSquares) { 
				if (cur - x < minFound) { break; }
				ans += seen[cur - x + shift];
			}
			seen[cur+shift]++; minFound = min(minFound, cur);
			if (seen[cur+shift] == 1) { used.push_back(cur+shift); }
		}

		cout << "Case #" << qq << ": " << ans << endl;
	}
}