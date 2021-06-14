#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int T; cin >> T;

	for (int z = 0; z < T; z++) {
		int N, B; cin >> N >> B;
		vector<int> nums(N);
		for (auto &x : nums) { cin >> x; }

		sort(nums.begin(), nums.end());
		int res = 0, i = 0;
		while (i < N && B >= nums[i]) {
			B -= nums[i];
			res++;
			i++;
		}

		cout << "Case #" << z + 1 << ": " << res << endl;
	}
}