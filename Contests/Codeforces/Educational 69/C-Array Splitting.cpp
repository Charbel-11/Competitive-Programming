#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
	int n, k;
	cin >> n >> k;

	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	
	if (k == 1) {
		cout << nums[n - 1] - nums[0] << endl;
		return 0;
	}

	multimap<int, int> diff;
	for (int i = 0; i < n - 1; i++) {
		diff.insert({ nums[i + 1] - nums[i], i+1 });
	}

	vector<int> cuts;
	multimap<int, int>::iterator itr = prev(diff.end());
	while (k > 1) {
		cuts.push_back(itr->second);
		k--;
		itr = prev(itr);
	}

	sort(cuts.begin(), cuts.end());

	int res = nums[cuts[0]-1] - nums[0];
	int newIndex = cuts[0];
	for (int i = 1; i < cuts.size(); i++) {
		res += nums[cuts[i] - 1] - nums[newIndex];
		newIndex = cuts[i];
	}
	res += nums[n - 1] - nums[newIndex];

	cout << res << endl;
}