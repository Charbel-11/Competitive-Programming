#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (auto &x : nums) { cin >> x; }
	sort(nums.begin(), nums.end());

	int res = 0;
	vector<bool> visited(n, 0);
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			visited[i] = true;
			res++;
			for (int j = i + 1; j < n; j++) {
				if (!visited[j] && nums[j]%nums[i] == 0) {
					visited[j] = true;
				}
			}
		}
	}

	cout << res << endl;
}
