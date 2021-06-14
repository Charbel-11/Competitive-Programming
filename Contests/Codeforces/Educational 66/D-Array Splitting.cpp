#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//The answer is 1*(S(p1)-S(p2)) + 2*(S(p2)-S(p3)) +... = S(p1)+S(p2)+...+S(pk) where S(pi) is the sum from j-1 to n-1
//S(p1)=S(1) since we can't miss any element
int main() {
	int n, k;
	cin >> n >> k;
	vector<int> nums(n);
	vector<long long> sums(n-1, 0);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	sums[n - 2] = nums[n - 1];
	for (int i = n - 3; i >= 0; i--) {
		sums[i] = sums[i + 1] + nums[i + 1];
	}

	long long res = sums[0] + nums[0];
	sort(sums.rbegin(), sums.rend());
	for (int i = 0; i < k-1; i++) {
		res += sums[i];
	}

	cout << res << endl;
}