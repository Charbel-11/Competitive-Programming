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

	int n; ll t; cin >> n >> t;
	vector<ll> nums(n); for (auto &x : nums) { cin >> x; }
	map<ll, vector<pair<int, int>>> m;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			m[nums[i] + nums[j]].push_back({ i+1,j+1 });
	
	for (auto& x : m) {
		ll y = t - x.first;
		for (auto& p1 : m[y]) {
			for (auto& p2 : x.second) {
				if (p1.first != p2.first && p1.first != p2.second && p1.second != p2.first && p1.second != p2.second) {
					cout << p1.first << " " << p2.first << " " << p1.second << " " << p2.second << '\n';
					return 0;
				}
			}
		}
	}

	cout << "IMPOSSIBLE\n";
}