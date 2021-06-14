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
		int n; cin >> n;

		int res = 0;

		vector<string> nums(n); map<string, int> freq;
		for (auto &x : nums) { cin >> x; freq[x]++; }
		for (auto &cur : freq) {
			if (cur.second <= 1) { continue; }
			else {
				int i = 0;
				while (cur.second > 1) {
					while (nums[i] != cur.first) { i++; }

					int count = 0;
					string temp = cur.first;
					while (count < 9 && freq[temp] >= 1) {
						temp[3] = temp[3] + 1;
						if (temp[3] > '9') { temp[3] = '0'; }
						count++;
					}
					if (count == 9) {
						temp = cur.first;
						temp[2] = temp[2] + 1;
						if (temp[2] > '9') { temp[2] = '0'; }
					}

					res++;
					nums[i] = temp; cur.second--; freq[temp] = 1;
				}
			}
		}

		cout << res << endl;
		for (auto &x : nums) { cout << x << endl; }
	}
}