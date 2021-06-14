#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	string s, t; cin >> s >> t;

	int as = 0, bs = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'a') { as++; }
		else { bs++; }
		if (t[i] == 'a') { as++; }
		else { bs++; }
	}

	if (as % 2 || bs % 2) { cout << -1 << endl; return 0; }

	vector<int> code(n);
	for (int i = 0; i < n; i++) {
		if (s[i] == t[i]) { code[i] = 0; }
		else if (s[i] == 'a') { code[i] = 1; }
		else { code[i] = 2; }
	}

	vector<pair<int, int>> answ;
	int i = 0;
	int j1 = 0, j2 = 0;
	while (i < n) {
		if (code[i] == 1) {
			if (j1 <= i) { j1 = i + 1; }
			while (j1 < n && code[j1] != 1) { j1++; }
			if (j1 == n) {
				if (j2 <= i) { j2 = i + 1; }
				while (j2 < n && code[j2] != 2) { j2++; }
				answ.push_back({ i + 1, i + 1 });
				answ.push_back({ i + 1, j2 + 1 });
				code[j2] = 0;
			}
			else {
				answ.push_back({ i + 1, j1 + 1 });
				code[j1] = 0;
			}
		}
		else if (code[i] == 2) {
			if (j2 <= i) { j2 = i + 1; }
			while (j2 < n && code[j2] != 2) { j2++; }
			if (j2 == n) {
				if (j1 <= i) { j1 = i + 1; }
				while (j1 < n && code[j1] != 1) { j1++; }
				answ.push_back({ i + 1, i + 1 });
				answ.push_back({ i + 1, j1 + 1 });
				code[j1] = 0;
			}
			else {
				answ.push_back({ i + 1, j2 + 1 });
				code[j2] = 0;
			}
		}
		i++;
	}

	cout << answ.size() << endl;
	for (auto &x : answ) { cout << x.first << " " << x.second << endl; }
}