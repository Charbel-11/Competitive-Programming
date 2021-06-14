#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	int t; cin >> t;

	while (t--) {
		int n; cin >> n;
		string s; cin >> s;

		map<int, int> nums; for (int i = 1; i <= n; i++) { nums.insert({ i, 0 }); }

		vector<int> less(n, 0);
		for(int i = n-2; i >=0; i--){
			if (s[i] == '>') { continue; }
			less[i] = less[i + 1] + 1;
		}
		vector<int> ansL;

		for (int i = 0; i < n - 1; i++) {
			if (s[i] == '>') {
				ansL.push_back(prev(nums.end())->first);
				nums.erase(--nums.end());
				continue;
			}

			int val = less[i];
			auto it = prev(nums.end());
			while (val) {
				it--; val--;
			}

			for (int j = 0; j < less[i]; j++) {
				ansL.push_back(it->first);
				it++;
				nums.erase(ansL.back());
			}

			i += less[i] - 1;
		}
		ansL.push_back(nums.begin()->first);
		for (auto &x : ansL) { cout << x << " "; } cout << endl;

		//SECOND PART

		nums.clear(); for (int i = 1; i <= n; i++) { nums.insert({ i, 0 }); }

		vector<int> more(n, 0);
		for (int i = n - 2; i >= 0; i--) {
			if (s[i] == '<') { continue; }
			more[i] = more[i + 1] + 1;
		}
		vector<int> ansM;

		for (int i = 0; i < n - 1; i++) {
			if (s[i] == '<') {
				ansM.push_back(nums.begin()->first);
				nums.erase(nums.begin());
				continue;
			}

			int val = more[i];
			auto it = nums.begin();
			while (val) {
				it++; val--;
			}

			for (int j = 0; j < more[i]; j++) {
				ansM.push_back(it->first);
				it--;
				nums.erase(ansM.back());
			}

			i += more[i] - 1;
		}
		ansM.push_back(nums.begin()->first);
		for (auto &x : ansM) { cout << x << " "; } cout << endl;
	}
}