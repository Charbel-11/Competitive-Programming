#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		vector<pair<int, int>> nums(n);
		for (int i = 0; i < n; i++) {
			string s; cin >> s;
			int curZ = 0, curO = 0;
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == '0') { curZ++; }
				else { curO++; }
			}
			nums[i] = { curZ, curO };
		}

		int res = 0;
		for (int i = 0; i < n; i++) {
			if (!(nums[i].first % 2 && nums[i].second % 2)) { 
				res++; 
				continue; 
			}
			for (int j = 0; j < n; j++) {
				if (j == i) { continue; }

				if (nums[j].first % 2) { 
					nums[j].first--; nums[j].second++;
					nums[i].first++; nums[i].second--;;
					res++; break;
				}
				else if (nums[j].second % 2) { 
					nums[j].second--; nums[j].first++;
					nums[i].second++; nums[i].first++;
					res++; break;
				}
			}
		}

		cout << res << endl;
	}
}