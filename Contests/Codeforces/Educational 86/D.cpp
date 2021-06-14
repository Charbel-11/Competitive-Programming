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

int n, k;
vector<ll> c;
vector<int> freq;

bool check(ll t) {
	ll used = 0;
	for (int i = k; i > 0; i--) {
		ll available = t * c[i] - used;
		if (freq[i] > available) { return false; }
		used += freq[i];
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> k;
	freq.resize(k + 1, 0); c.resize(k + 1, 0);
	for (int i = 0; i < n; i++) {
		int temp; cin >> temp;
		freq[temp]++;
	}
	for (int i = 1; i <= k; i++) { cin >> c[i]; }

	ll l = 0, r = n;
	while (l < r) {
		ll mid = (l + r) / 2;
		bool b = check(mid);
		if (b) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << '\n'; 
	vector<vector<int>> ans(l);

	int idx = 0;
	for (int i = 1; i <= k; i++)
		for (int j = 0; j < freq[i]; j++)
			ans[idx++%l].push_back(i);

	for (auto &v : ans) {
		cout << v.size() << " ";
		for (auto &x : v) { cout << x << " "; }
		cout << endl;
	}
}