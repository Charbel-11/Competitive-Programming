#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> distNums;
vector<int> repeatedNums;
//Having a vector nums of n SORTED ints, create a vector of distinct ints in order
void makeDistinct(vector<int> nums) {
	distNums.clear();				
	repeatedNums.clear();

	int n = nums.size();
	if (n == 0) { return; }

	int i = 0;
	while (i < n - 1) {
		if (nums[i] != nums[i + 1]) {
			distNums.push_back(nums[i]);
			i++;
			continue;
		}

		distNums.push_back(nums[i]);
		while (i < n - 1 && nums[i] == nums[i + 1]) {
			repeatedNums.push_back(nums[i]);
			i++;
		}
		i++;
	}
	if (n == 1 || (n > 1 && nums[n - 2] != nums[n - 1])) { distNums.push_back(nums[n - 1]); }
}

int main() {
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	sort(nums.begin(), nums.end());

	makeDistinct(nums);

	int s = repeatedNums.size();
	for (int i = 0; i < s - 1; i++) {			//putting repeatedNums.size()-1 gave a big positive number when size is 0
		if (repeatedNums[i] == repeatedNums[i + 1]) {
			cout << "NO" << endl;
			return 0;
		}
	}
	sort(repeatedNums.rbegin(), repeatedNums.rend());
	
	cout << "YES" << endl;
	cout << distNums.size() << endl;
	for (int i = 0; i < distNums.size(); i++) {
		cout << distNums[i] << " ";
	}
	cout << endl;

	cout << repeatedNums.size() << endl;
	for (int i = 0; i < repeatedNums.size(); i++) {
		cout << repeatedNums[i] << " ";
	}
	cout << endl;
}