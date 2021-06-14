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
		int n; cin >> n;

		vector<int> candidates;
		if (n % 2 == 0) { candidates.push_back(n / 2); }
		if (n % 4 == 0) { candidates.push_back(n / 4); }

		bool OK = false;
		for(auto cur : candidates){
			int d = 1;
			while (d * d < cur) { d++; }
			if (d * d == cur) { OK = true; break; }
		}

		cout << (OK ? "YES" : "NO") << '\n';
	}
}
