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
		string s; cin >> s; int n = s.size();
		char op = s[0], close = s.back();
		if (op == close) { cout << "NO" << '\n'; continue; }
		
		bool OK = true;
		int curO = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == op) { curO++; }
			else if (s[i] == close) { curO--; }
			else { curO++; }
			if (curO < 0) { OK = false; break; }
		}
		if (OK && curO == 0) { cout << "YES" << '\n'; continue; }

		OK = true;
		curO = 0;
		for (int i = 0; i < n; i++) {
			if (s[i] == op) { curO++; }
			else if (s[i] == close) { curO--; }
			else { curO--; }
			if (curO < 0) { OK = false; break; }
		}
		if (OK && curO == 0) { cout << "YES" << '\n'; continue; }
		cout << "NO" << '\n';
	}
}