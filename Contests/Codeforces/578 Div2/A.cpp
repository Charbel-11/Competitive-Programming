#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> nums(10, 0);
	string s;
	cin >> s;

	for (int i = 0; i < n; i++) {
		if (s[i] == 'L') {
			for (int j = 0; j < 10; j++) {
				if (nums[j] == 0) {
					nums[j] = 1;
					break;
				}
			}
		}
		else if (s[i] == 'R') {
			for (int j = 9; j >= 0; j--) {
				if (nums[j] == 0) {
					nums[j] = 1;
					break;
				}
			}
		}
		else {
			nums[s[i] - '0'] = 0;
		}
	}

	for (int i = 0; i < 10; i++) {
		cout << nums[i];
	}
	cout << endl;
}