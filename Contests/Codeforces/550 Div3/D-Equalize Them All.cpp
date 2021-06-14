#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;

	unordered_map<int, int> freq;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
		if (freq.count(nums[i]) != 0) {
			freq[nums[i]]++;
		}
		else {
			freq[nums[i]] = 1;
		}
	}

	unordered_map<int, int>::iterator itr = freq.begin();
	int maxFreq = itr->second;
	int maxNum = itr->first;

	itr++;
	while (itr != freq.end()) {
		if (itr->second > maxFreq) {
			maxNum = itr->first;
			maxFreq = itr->second;
		}
		itr++;
	}

	int opNum = n - maxFreq;
	cout << opNum << endl;
	int i = 0;
	bool add = true;
	while (opNum != 0) {
		if (nums[i] == maxNum) {
			if (i > 0 && nums[i - 1] != maxNum) {
				if (nums[i - 1] < maxNum) {
					cout << "1 " << i << " " << i + 1 << endl;
					nums[i - 1] = maxNum;
				}
				else {
					cout << "2 " << i << " " << i + 1 << endl;
					nums[i - 1] = maxNum;
				}
				opNum--;
			}
			if (i < n - 1 && nums[i + 1] != maxNum) {
				if (nums[i + 1] < maxNum) {
					cout << "1 " << i + 2 << " " << i + 1 << endl;
					nums[i + 1] = maxNum;
				}
				else {
					cout << "2 " << i + 2 << " " << i + 1 << endl;
					nums[i + 1] = maxNum;
				}
				opNum--;
			}
		}
		if (i == n - 1) {
			add = false;
		}
		else if (i == 0) {
			add = true;
		}

		if (add) { i++; }
		else { i--; }
	}
}