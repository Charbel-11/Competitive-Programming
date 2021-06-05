#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }

	int mid = (k % 2 ? k / 2 : k / 2 - 1), cur;

	multiset<int> smaller, bigger;
	vector<int> temp;
	for (int i = 0; i < k; i++) { temp.push_back(nums[i]); }
	sort(temp.begin(), temp.end());

	for (int i = 0; i <= mid; i++) { smaller.insert(temp[i]); }
	for (int i = mid + 1; i < k; i++) { bigger.insert(temp[i]); }
	cur = *(prev(smaller.end()));
	cout << cur << ' ';
	
	for (int i = k; i < n; i++) {
		if (nums[i - k] <= cur) { smaller.erase(smaller.find(nums[i - k])); }
		else { bigger.erase(bigger.find(nums[i - k])); }

		if (nums[i] <= cur) { smaller.insert(nums[i]); }
		else { bigger.insert(nums[i]); }
		
		while (smaller.size() < bigger.size()) {
			smaller.insert(*bigger.begin());
			bigger.erase(bigger.begin());
		}
		while (smaller.size() > bigger.size() + 1) {
			bigger.insert(*prev(smaller.end()));
			smaller.erase(prev(smaller.end()));
		}
		cur = *(prev(smaller.end()));
		cout << cur << ' ';
	}
}