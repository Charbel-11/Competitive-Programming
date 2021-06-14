#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

string s;

int main() {
	int t; cin >> t;

	for (int z = 0; z < t; z++) {
		int n; cin >> n;
		cin >> s;

		bool OK = false;
		vector<bool> color;
		for (int i = 0; i < 10; i++) {
			color.resize(n, 0);
			int curMax0 = 0, curMin1 = -1;
			int curMax1 = 0;
			for (int j = 0; j < n; j++) {
				int num = s[j] - '0';
				if (num > i) { 
					color[j] = 1;
					if (curMin1 == -1) { curMin1 = num; }
					if (curMax1 > num) { 
						if (curMax0 > num || (curMin1 != -1 && num > curMin1)) { break; }
						curMax0 = num;
						color[j] = 0;
					}
					else {
						curMax1 = num;
					}
				}
				else {
					if (num < curMax0) { break; }
					else { curMax0 = num; color[j] = 0; }
				}

				if (j == n - 1) { OK = true; }
			}
			if (OK) { break; }
		}

		if (OK){
			for (int i = 0; i < color.size(); i++) { cout << color[i] + 1; }
			cout << endl;
		}
		else {
			cout << "-" << endl;
		}
	}
}