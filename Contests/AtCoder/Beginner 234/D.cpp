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

	int n, k; cin >> n >> k;
	vector<int> p(n); for (auto& x : p) { cin >> x; }

	set<int> m;
	for (int i = 0; i < k; i++) { m.insert(p[i]); }
	
	auto it = m.begin();
	int curAns = *it;

	cout << curAns << '\n';
	for (int i = k; i < n; i++) {
		m.insert(p[i]);
		if (p[i] > curAns) { it++; curAns = *it; }
		cout << curAns << '\n';
	}
}