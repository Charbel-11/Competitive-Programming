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
	vector<int> A(n), B(n);
	for (auto& x : A) { cin >> x; }
	for (auto& x : B) { cin >> x; }

	int ans1 = 0, ans2 = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] == B[i]) { ans1++; }
		for (int j = 0; j < n; j++) {
			if (i == j) { continue; }
			if (A[i] == B[j]) { ans2++; }
		}
	}

	cout << ans1 << '\n' << ans2 << '\n';
}