#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;

		set<int> unmatched;
		vector<vector<int>> d(n);
		for (int i = 0; i < n; i++) {
			int k; cin >> k;
			while (k--) {
				int temp; cin >> temp;
				d[i].push_back(temp);
			}
			unmatched.insert(i + 1);
		}
		int matched = 0;
		
		int toMatch = -1;
		for (int i = 0; i < n; i++) {
			if (d[i].size() == 0) { toMatch = i+1; continue; }
			bool mm = false;
			for (int j = 0; j < d[i].size(); j++) {
				if (unmatched.count(d[i][j])) {
					unmatched.erase(d[i][j]); matched++; 
					mm = true; break;
				}
			}
			if (!mm) { toMatch = i+1; }
		}

		if (matched == n) { cout << "OPTIMAL" << endl; continue; }
		cout << "IMPROVE" << endl;
		cout << toMatch << " " << *unmatched.begin() << endl;
	}
}