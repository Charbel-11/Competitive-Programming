#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		string s; cin >> s;
		vector<int> ones;

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '1') { ones.push_back(i); }
		}

		long long res = 0;
		for (int i = 0; i < s.size(); i++) {
			int k = lower_bound(ones.begin(), ones.end(), i) - ones.begin();
			if (k == ones.size()) { break; }

			int j = ones[k];
			long long num = 0;
			while (j < s.size()) {
				num <<= 1;
				if (s[j] == '1') { num++; }
				int range = j - i + 1;
				if (range == num) { res++; }
				else if (range < num) { break; }
				j++;
			}
		}

		cout << res << endl;
	}
}