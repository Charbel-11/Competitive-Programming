#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 60;

// Runs in O(min(n,m).nm)
pair<int, int> GaussianElimination(vector<bitset<N>>& a, int n, int m) {
	int det = 1, rank = 0;

	for (int col = 0; col < m; col++) {
		if (rank == n) { det = 0; break; }
		for (int i = rank; i < n; ++i) {
			if (a[i][col]) {
				swap(a[i], a[rank]);
				break;
			}
		}
		if (!a[rank][col]) { det = 0; continue; }

		for (int i = 0; i < n; i++) {
			if (i != rank && a[i][col])
				a[i] ^= a[rank];
		}
		rank++;
	}

	return { rank, det };
}

string decimalToReverseBinary(int x, int n) {
	string ans = "";

	while (x) {
		if (x & 1) { ans.push_back('1'); }
		else { ans.push_back('0'); }
		x /= 2;
	}
	while(ans.size() < n) { ans.push_back('0'); }

	return move(ans);
}

int reversedBinaryToDecimal(const string& s) {
	int ans = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		ans *= 2;
		if (s[i] == '1') { ans += 1; }
	}
	return ans;
}

int getMax(int i, int curB, vector<bitset<N>>& nums) {
	vector<bitset<N>> curNums;
	for (int j = i; j < nums.size(); j++) {
		string curStr = nums[j].to_string(); 		
		int curNumB = reversedBinaryToDecimal(string(curStr.begin(), curStr.begin() + 30));
		string bStr = decimalToReverseBinary(curNumB, 60);
		curNums.push_back(bitset<N>(bStr));
	}

	GaussianElimination(curNums, nums.size() - i, 60);
	
	ll ans = curB;
	for (auto& bitS : curNums) {
		ll curNumB = reversedBinaryToDecimal(bitS.to_string());
		ans = max(ans, ans ^ curNumB);
	}
	return ans;
}

int getMaxWithConstraints(int i, int j, int curA, int curB, int k, bool used, vector<bitset<N>>& nums) {
	if (i == nums.size()) { return ((curA <= k && used) ? curB : -1); }

	while (j < 30 && !nums[i][j]) { j++; }
	int curPower = 30 - j - 1; 
	int allOnes = (1 << (curPower + 1)) - 1;
	if ((curA & (~allOnes)) > k) { return -1; }
	if (j >= 30 || (curA | allOnes) <= k) { return getMax(i, curB, nums); }

	int ans = -1; string curStr = nums[i].to_string(); 
	int curNumA = reversedBinaryToDecimal(string(curStr.begin() + 30, curStr.end()));
	int curNumB = reversedBinaryToDecimal(string(curStr.begin(), curStr.begin() + 30));
	ans = max(ans, getMaxWithConstraints(i + 1, j + 1, curA, curB, k, false, nums));
	ans = max(ans, getMaxWithConstraints(i + 1, j + 1, curA ^ curNumA, curB ^ curNumB, k, true, nums));

	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	vector<bitset<N>> nums;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
		
		string aStr = decimalToReverseBinary(a, 30), bStr = decimalToReverseBinary(b, 30);
		nums.push_back(bitset<N>(bStr + aStr));
	}

	GaussianElimination(nums, n, 60);
	while (!nums.empty() && nums.back().count() == 0) {
		nums.pop_back(); 
	}

	if (nums.empty()) { cout << 0 << '\n'; }
	else { cout << getMaxWithConstraints(0, 0, 0, 0, k, false, nums) << '\n'; }
}