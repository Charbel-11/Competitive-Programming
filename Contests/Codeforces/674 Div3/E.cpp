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

	int n; cin >> n;
	vector<int> A(3), B(3);
	for (auto &x : A) { cin >> x; }
	for (auto &x : B) { cin >> x; }

	int maxWin = 0, minWin = 0;
	for (int i = 0; i < 3; i++) {
		maxWin += min(A[i], B[(i + 1) % 3]);
	}
	for (int i = 0; i < 3; i++) {
		minWin += max(0, A[i] - B[i] - B[(i + 2) % 3]);
	}

	cout << minWin << ' ' << maxWin << '\n';
}