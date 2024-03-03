#include <iostream>
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
	sort(A.begin(), A.end());

	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] == ans) { ans++; }
		else if (A[i] > ans) { break; }
	}

	cout << ans << '\n';
}
