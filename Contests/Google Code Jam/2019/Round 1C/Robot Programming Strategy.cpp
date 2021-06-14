#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool possible;
string ans;
vector<string> robots;

void addStr(string& s1, string& s2) {
	for (int i = 0; i < s2.size(); i++) {
		s1.push_back(s2[i]);
	}
}

//P R S
void findMove(int round, int l, int r) {
	int R = 0, P = 0, S = 0;

	for (int i = l; i <= r; i++) {
		if (robots[i][round] == 'R') R++;
		if (robots[i][round] == 'P') P++;
		if (robots[i][round] == 'S') S++;
	}

	if (R && P && S) { possible = false; return; }
	if (R && P) { ans.push_back('P'); findMove(round + 1, l, l + P - 1); }
	else if (R && S) { ans.push_back('R'); findMove(round + 1, l, l + R - 1); }
	else if (P && S) { ans.push_back('S'); findMove(round + 1, l + P, r); }
	else if (R) { ans.push_back('P'); }
	else if (P) { ans.push_back('S'); }
	else { ans.push_back('R'); }
}

int main() {
	int T; cin >> T;

	for (int q = 1; q <= T; q++) {
		int A; cin >> A;
		robots.clear(); robots.resize(A);
		for (auto &x : robots) {
			cin >> x;
			string cur = x;
			while (x.size() < 500) {
				addStr(x, cur);
			}
		}

		sort(robots.begin(), robots.end());
		possible = true;
		ans = "";

		findMove(0, 0, A - 1);

		cout << "Case #" << q << ": ";
		if (!possible) { cout << "IMPOSSIBLE" << endl; }
		else { cout << ans << endl; }
	}
}