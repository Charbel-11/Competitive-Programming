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
		vector<int> x(n); for (auto& xx : x) { cin >> xx; }

		set<int> used;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int curA = x[j] - x[i];
				used.insert(curA);
			}
		}

		cout << used.size() << '\n';
	}
}