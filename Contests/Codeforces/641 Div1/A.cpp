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

vector<pair<ll, int>> primeFactors(ll x) {
	vector<pair<ll, int>> ans;
	ll num = 2;
	while (x != 1 && num*num <= x) {
		if (x % num == 0) {
			int k = 0;
			while (x % num == 0) {
				x /= num; k++;
			}
			ans.push_back({ num,k });
		}
		num++;
	}
	if (x != 1) { ans.push_back({ x,1 }); }
	return move(ans);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<ll> nums(n);
	map<ll, vector<int>> m;
	for (auto &x : nums) { 
		cin >> x;
	
		vector<pair<ll, int>> vp = primeFactors(x);
		for (auto &p : vp) {
			m[p.first].push_back(p.second);
		}
	}

	ll ans = 1;
	for (auto &u : m) {
		if (u.second.size() < n - 1) { continue; }
		if (u.second.size() == n - 1) { u.second.push_back(0); }
		sort(u.second.begin(), u.second.end());
		int mult = u.second[1];
		while (mult--) {
			ans *= u.first;
		}
	}

	cout << ans << endl;
}