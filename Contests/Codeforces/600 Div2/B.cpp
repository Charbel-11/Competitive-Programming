#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	vector<int> a(n);
	for (auto &x : a) { cin >> x; }

	vector<int> answ;
	set<int> cur; set<int> seen;
	int curSize = 0; bool OK = true;
	for (int i = 0; i < n; i++) {
		curSize++;
		if (a[i] > 0) {
			if (seen.count(a[i])) {
				OK = false; break;
			}
			cur.insert(a[i]); seen.insert(a[i]);
		}
		else {
			if (cur.count(-a[i]) == 0) {
				OK = false; break;
			}
			else {
				cur.erase(-a[i]);
			}
		}
		if (cur.empty()) {
			answ.push_back(curSize);
			curSize = 0;
			seen.clear();
		}
	}

	if (!cur.empty()) { OK = false; }

	if (!OK) { cout << -1 << endl; }
	else {
		cout << answ.size() << endl;
		for (auto &x : answ) { cout << x << " "; }cout << endl;
	}
}