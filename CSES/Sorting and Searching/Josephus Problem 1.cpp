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

	int n; cin >> n;
	set<int> cur;
	for (int i = 1; i <= n; i++) { cur.insert(i); }

	auto it = cur.begin();
	while (cur.size()) {
		it++; if (it == cur.end()) { it = cur.begin(); }
		int curA = *it; cout << curA << ' ';
		it++; if (it == cur.end()) { it = cur.begin(); }
		cur.erase(curA);
	}
	cout << '\n';
}