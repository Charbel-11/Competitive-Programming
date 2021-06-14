#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector<bool> states(n);
	for (int i = 0; i < n; i++) {
		bool b = s[i] == 'R';
		states[i] = b;
	}

	vector<vector<int>> m; int totalMoves = 0;
	while(true) {
		bool OK = false;
		vector<int> cur;
		for (int i = 0; i < n - 1; i++) {
			if (states[i] == 1 && states[i + 1] == 0) {
				swap(states[i], states[i + 1]);
				cur.push_back(i+1); totalMoves++;
				OK = true; i++;
			}
		}
		if (!OK) { break; }
		m.emplace_back(cur);
	}

	while (!m.empty() && m.back().size() == 0) { m.pop_back(); }

	int last = m.size();
	if (totalMoves < k || last > k) { cout << -1 << endl; return 0; }
	int needed = k - last;

	for (auto &movesT : m) {
		while (movesT.size() && needed) {
			cout << 1 << " " << movesT.back() << "\n";
			movesT.pop_back(); needed--;
		}
		if (movesT.empty()) { needed++; continue; }
		cout << movesT.size() << " ";
		for (auto &move : movesT) { cout << move << " "; }
		cout << "\n";
	}
}