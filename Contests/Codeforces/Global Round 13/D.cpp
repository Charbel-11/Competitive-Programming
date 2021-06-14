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

	int t; cin >> t;
	while (t--) {
		int u, v; cin >> u >> v;
		if (u > v) { cout << "No" << '\n'; continue; }
		
		vector<int> uB, vB;
		while (u) { uB.push_back(u & 1); u >>= 1; }
		while (v) { vB.push_back(v & 1); v >>= 1; }
		while (uB.size() < vB.size()) { uB.push_back(0); }

		bool OK = true;
		for (int i = 0; i < uB.size(); i++) {
			if (i) { uB[i] += uB[i - 1]; vB[i] += vB[i - 1]; }
			if (vB[i] > uB[i]) { OK = false; break; }
		}

		cout << (OK ? "Yes" : "No") << '\n';
	}
}