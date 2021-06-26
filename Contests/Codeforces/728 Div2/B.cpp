#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#define deb(x) cout << #x << " " << x 
using namespace std;
typedef long long ll;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<pair<ll, int>> nums(n);
		for (int i = 0; i < n; i++) {
			cin >> nums[i].first; nums[i].second = i + 1;
		}
		sort(nums.begin(), nums.end());
		
		ll ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (nums[i].first * nums[j].first > 2ll * n) { break; }
				if (nums[i].first * nums[j].first == nums[i].second + nums[j].second) { ans++; }
			}
		}

		cout << ans << '\n';
	}
}