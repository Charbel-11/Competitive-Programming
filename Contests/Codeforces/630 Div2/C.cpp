#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	while (t--) {
		int n, k; cin >> n >> k;
		string s; cin >> s;
		vector<int> comp(n, -1);
		int count = 1;

		map<int, vector<int>> groups;
		for (int j = 0; j < k; j++) {
			if (comp[j] != -1) { continue; }
			vector<int> parallelPoints;
			for (int i = j; i < n; i += k) { 
				comp[i] = count; groups[count].push_back(i);
				parallelPoints.push_back(n - i - 1); 
			}
			for (int p : parallelPoints) {
				if (comp[p] == -1) {
					for (int i = p; i < n; i += k) {
						if (comp[i] == -1) { groups[count].push_back(i); }
						comp[i] = count; 
						if (comp[n - i - 1] == -1) { parallelPoints.push_back(n - i - 1); }
					}
					for (int i = p - k; i >= 0; i -= k) {
						if (comp[i] == -1) { groups[count].push_back(i); }
						comp[i] = count;
						if (comp[n - i - 1] == -1) { parallelPoints.push_back(n - i - 1); }
					}
				}
			}
			count++;
		}

		int ans = 0;
		for (auto &v : groups) {
			map<char, int> m;
			int mma = 0;
			for (auto &i : v.second) {
				m[s[i]]++;
				mma = max(mma, m[s[i]]);
			}
			ans += (v.second.size() - mma);
		}

		cout << ans << endl;
	}
}