#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;

bool query(int u, int v) {
	cout << "? " << u << " " << v << endl;
	string res; cin >> res;
	return res == "Yes";
}

int main() {
	int n; cin >> n;
	vector<int> k(n); for (auto& x : k) { cin >> x; }

	vector<pair<int, pair<int, int>>> v;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int u1 = i, u2 = j;
			if (k[u1] > k[u2]) { swap(u1, u2); }
			v.push_back({ k[u2] - k[u1], {u1, u2} });
		}
	}

	sort(v.rbegin(), v.rend());

	for (auto& p : v) {
		int u1 = p.second.first + 1, u2 = p.second.second + 1;
		if (query(u2, u1)) {
			cout << "! " << u1 << " " << u2 << endl; 
			return 0;
		}
	}

	cout << "! 0 0" << endl;
}
