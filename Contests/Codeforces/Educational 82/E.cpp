#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> Choice;
string s; string t;

bool check2(int curJ) {
	int prevJ = 0; int used = Choice[0];

	for (int i = 0; i < s.size() && curJ < t.size(); i++) {
		if (i == used) { 
			if (prevJ != t.size() - 1) 
				used = Choice[++prevJ]; 
			continue; 
		}

		if (s[i] == t[curJ]) { curJ++; }
	}

	return curJ == t.size();
}

bool check(int cut, int curI, int curJ) {
	if (curJ == cut) { return check2(cut); }

	int i = curI;
	while (true) {
		while (i < s.size() && s[i] != t[curJ]) { i++; }
		if (i == s.size()) { break; }
		Choice[curJ] = i;
		bool b = check(cut, i, curJ + 1);
		if (b) return true;
		i++;
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int tt; cin >> tt;

	while (tt--) {
		cin >> s >> t;

		bool OK = false;
		for (int i = 0; i <= s.size(); i++) {
			Choice.clear(); Choice.resize(t.size(), -1);

			if (check(i, 0, 0)) { 
				OK = true; break; 
			}
		}

		cout << (OK ? "YES" : "NO") << endl;
	}
}