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

	int x, n; cin >> x >> n;
	set<int> lights; lights.insert(0); lights.insert(x);
	multiset<int> candidates; candidates.insert(x);

	for (int i = 0; i < n; i++) {
		int p; cin >> p;
		auto itNext = lights.upper_bound(p);
		auto itPrev = prev(itNext);

		candidates.erase(candidates.find(*itNext - *itPrev));
		candidates.insert(p - *itPrev);
		candidates.insert(*itNext - p);
		lights.insert(p);
		cout << *(prev(candidates.end())) << ' ';
	}
	cout << '\n';
}