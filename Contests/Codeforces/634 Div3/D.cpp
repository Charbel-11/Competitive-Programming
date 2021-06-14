#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
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
		vector<string> grid(9);
		for (auto &s : grid) { cin >> s; }
		int offset = -1;
		for (int i = 0; i < 9; i++) {
			if (i % 3 == 0) { offset++; }
			int mult = i % 3;
			char cur = grid[i][mult * 3 + offset];
			int temp = cur - '0'; temp++; temp %= 10;
			if (temp == 0) { temp++; }
			cur = temp + '0';
			grid[i][mult * 3 + offset] = cur;
		}
		for (auto &s : grid) { cout << s << endl; }
	}
}