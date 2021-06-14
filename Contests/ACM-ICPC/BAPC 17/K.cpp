#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	int n; cin >> n;

	vector<vector<int>> canBeat(n);
	vector<int> used(n, 0);

	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		for (int j = 0; j < n; j++) {
			if (s[j] == '1') {
				canBeat[i].push_back(j);
			}
		}
	}

	vector<int> answ; answ.push_back(0); used[0] = 1;
	queue<int> S; S.push(0);

	while (!S.empty()) {
		int cur = S.front(); S.pop();

		for (auto &x : canBeat[cur]) {
			if (!used[x]) {
				answ.push_back(x);
				S.push(x);
				used[x] = 1;
			}
		}
	}

	if (answ.size() != n) { cout << "impossible" << endl; return 0; }

	reverse(answ.begin(), answ.end());
	for (auto &x : answ) {
		cout << x << " "; 
	}
	cout << endl;
}