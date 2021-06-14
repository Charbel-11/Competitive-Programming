#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	string s; cin >> s;
	vector<int> open, closed;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') { open.push_back(i); }
		else { closed.push_back(i); }
	}

	vector<int> ans;

	int i = 0, j = closed.size() - 1;
	while (i < open.size() && j >= 0) {
		if (open[i] < closed[j]) {
			ans.push_back(open[i]); ans.push_back(closed[j]);
		}
		i++; j--;
	}

	if (ans.empty()) { cout << 0 << endl; return 0; }

	cout << 1 << endl;
	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for (auto &x : ans) {
		cout << x + 1 << " ";
	}
	cout << endl;
}