#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	int n, r; cin >> n >> r;

	multiset<pair<int, int>> pos;
	multiset<pair<int, int>> neg;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		if (b >= 0) {
			pos.insert({ a, b });
		}
		else {
			neg.insert({ a, b });
		}
	}

	multiset<pair<int, int>>::iterator itr = pos.begin();
	while (itr != pos.end()) {
		if (r < itr->first) { cout << "NO" << endl; return 0; }
		r += itr->second;
		itr++;
	}

	if (!neg.empty()) {
		itr = prev(neg.end());
		while (true) {
			if (r < itr->first) { cout << "NO" << endl; return 0; }
			r += itr->second;

			if (itr == neg.begin()) { break; }
			itr = prev(itr);
		}
	}

	if (r < 0) { cout << "NO" << endl; }
	else { cout << "YES" << endl; }
}