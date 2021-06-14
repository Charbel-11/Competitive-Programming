#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> A(n); for (auto& x : A) { cin >> x; }
	stack<int> S; S.push(-1);

	int ans = 0;
	for (int i = 0; i < n; i++) {
		while (S.size() > 1 && A[S.top()] >= A[i]) {
			int height = A[S.top()]; S.pop();
			ans = max(ans, height * (i - S.top() - 1));
		}
		S.push(i);
	}
	while (S.size() > 1) {
		int height = A[S.top()]; S.pop();
		ans = max(ans, height * (n - 1 - S.top()));
	}

	cout << ans << '\n';
}