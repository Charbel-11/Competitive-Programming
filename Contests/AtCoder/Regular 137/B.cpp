#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int maxSubarraySum(vector<int>& A) {
	int ans = 0, curAns = 0;
	for (int i = 0; i < A.size(); i++) {
		curAns += A[i];
		if (curAns < 0) { curAns = 0; }
		ans = max(ans, curAns);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> A(n); for (auto& x : A) { cin >> x; }

	for (int i = 0; i < n; i++) {
		if (A[i] == 0) { A[i] = 1; }
		else { A[i] = -1; }
	}
	int ans = 1 + maxSubarraySum(A);
	for (int i = 0; i < n; i++) { A[i] *= -1; }
	ans += maxSubarraySum(A);

	cout << ans << '\n';
}