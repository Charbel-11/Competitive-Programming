#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	int n, m; cin >> n >> m;

	vector<string> s(n), t(m);
	for (auto &x : s) { cin >> x; }
	for (auto &x : t) { cin >> x; }

	int q; cin >> q;
	while (q--) {
		int y; cin >> y; y--;
		cout << s[y%s.size()] + t[y%t.size()] << endl;
	}
}