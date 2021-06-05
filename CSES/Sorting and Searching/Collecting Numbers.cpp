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
	vector<int> x(n); for (auto& xx : x) { cin >> xx; }
	vector<int> idx(n + 1); idx[0] = n + 2;
	for (int i = 1; i <= n; i++) { idx[x[i - 1]] = i; }
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (idx[i] < idx[i - 1]) { ans++; }
	}
	cout << ans << '\n';
}