#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	multimap<pair<int, int>, int> segments;
	multimap<int, int> cur;
	for (int i = 0; i < n; i++) {
		int l, r; cin >> l >> r; l--; r--;
		segments.insert({ { l, r }, i+1 });
	}
	vector<int> res;
	auto it = segments.begin();
	for (int i = 0; i < 2e5+1; i++) {
		while (it != segments.end() && it->first.first <= i) {
			cur.insert({ it->first.second, it->second });
			it++;
		}
		while (!cur.empty() && cur.begin()->first < i) { cur.erase(cur.begin()); }
		while (cur.size() > k) {
			res.push_back(prev(cur.end())->second);
			cur.erase(prev(cur.end()));
		}
	}

	cout << res.size() << endl;
	for (auto &x : res) { cout << x << " "; }
}