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

	int n, m; cin >> n >> m;
	multiset<int> tickets;
	for (int i = 0; i < n; i++) { int cur; cin >> cur; tickets.insert(cur); }

	for (int i = 0; i < m; i++) {
		int cur; cin >> cur;

		auto it = tickets.upper_bound(cur);
		if (it == tickets.begin()) { cout << -1 << '\n'; }
		else { it--; cout << *it << '\n'; tickets.erase(it); }
	}
}