#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

//Too slow
vector<int> nums;
int DP[200002];
int backTrack[200002];

//Longest increasing subsequence including i
int LIS(int i) {
	int n = nums.size();
	if (i >= n) { return 0; }
	if (DP[i] != -1) { return DP[i]; }

	int maxLen = 1;
	for (unsigned int j = i + 1; j < n; j++) {
		int curLen = 0;

		if (nums[j] > nums[i]) {
			curLen += 1 + LIS(j);
		}

		if (curLen > maxLen) {
			backTrack[i] = j;
			maxLen = curLen;
		}
	}

	DP[i] = maxLen;
	return maxLen;
}

void resetDP() {
	for (int i = 0; i < 200002; i++) {
		DP[i] = -1;
		backTrack[i] = -1;
	}
}

int main() {
	nums.clear();
	resetDP();

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		nums.push_back(t);
	}

	int maxLen = 0;
	int startPoint = 0;
	for (int i = 0; i < n; i++) {
		int curLen = LIS(i);

		if (curLen > maxLen) {
			startPoint = i;
			maxLen = curLen;
		}
	}
	
		vector<int> answ(n, 1);
		int cur = startPoint;
		while (cur != -1) {
			answ[cur] = 0;
			cur = backTrack[cur];
		}
		
		int start = INT_MAX;
		for (int i = 0; i < n; i++) {
			if (answ[i] == 1 && nums[i] < start) {
				start = nums[i];
			}
			else if (answ[i] == 1 && nums[i] >= start) {
				cout << "NO" << endl;
				return 0;
			}
		}

		cout << "YES" << endl;
		for (int i = 0; i < n; i++) {
			cout << answ[i] << " ";
		}
		cout << endl;
}