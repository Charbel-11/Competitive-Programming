#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int main() {
	int n; cin >> n;

	vector<pair<ll, int>> nums(n); 
	for (int i = 0; i < n; i++) {
		int t; cin >> t;
		nums[i] = { t, i + 1 };
	}

	sort(nums.rbegin(), nums.rend());

	ll res = 0;
	int x = 0;
	vector<int> answ;
	for (int i = 0; i < n; i++) {
		res += (nums[i].first * x + 1);
		x++;
		answ.push_back(nums[i].second);
	}

	cout << res << endl;
	for (auto &x : answ) { cout << x << " "; }
	cout << endl;
}