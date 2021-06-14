#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;
typedef long long ll;

int main() {
	int n; cin >> n;

	map<int, ll> ans;
	for (int i = 0; i < n; i++) {
		int cur; cin >> cur;
		int diff = cur - i - 1;
		ans[diff] += cur;
	}

	ll finalAns = 0;
	for (auto &x : ans) { finalAns = max(finalAns, x.second); }

	cout << finalAns << endl;
}