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
	vector<pair<ll, ll>> task(n);
	for (auto &p : task) { cin >> p.first >> p.second; }
	sort(task.begin(), task.end());

	ll cur = 0, res = 0;
	for (int i = 0; i < n; i++) {
		cur += task[i].first;
		res += (task[i].second - cur);
	}

	cout << res << '\n';
}