#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
using namespace std;
typedef long long ll;

vector<vector<string>> grayCode2D(int n) {
	if (n == 1) { return { {"00", "01"}, {"10","11" } }; }

	vector<vector<string>> smallerGrayCode = grayCode2D(n - 1);
	vector<vector<string>> ans = smallerGrayCode;

	for (auto& v : ans)
		for (auto& s : v)
			s.push_back('0');
	for (int i = 0; i < smallerGrayCode.size(); i++) {
		for (int j = smallerGrayCode[i].size() - 1; j >= 0; j--) {
			ans[i].push_back(smallerGrayCode[i][j]);
			ans[i].back().push_back('1');
		}
	}

	smallerGrayCode = ans;
	for (auto& v : ans)
		for (auto& s : v)
			s.push_back('0');
	for (int i = smallerGrayCode.size() - 1; i >= 0; i--) {
		ans.push_back(smallerGrayCode[i]);
		for (auto& s : ans.back()) {
			s.push_back('1');
		}
	}

	return move(ans);
}

int invertedBinaryToDecimal(string& s) {
	int num = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		num *= 2;
		if (s[i] == '1') { num++; }
	}
	return num;
}

int main() {
	int n, k; cin >> n >> k;

	map<int, pair<int, int>> m;
	vector<vector<string>> gridStrInverted = grayCode2D(5);
	vector<vector<int>> grid(n, vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = invertedBinaryToDecimal(gridStrInverted[i][j]);
			m[grid[i][j]] = { i,j };
		}
	}

	vector<vector<int>> gridRight(n, vector<int>(n - 1, 0));
	vector<vector<int>> gridBot(n - 1, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			gridRight[i][j] = grid[i][j] ^ grid[i][j + 1];
		}
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n - 1; i++) {
			gridBot[i][j] = grid[i][j] ^ grid[i + 1][j];
		}
	}

	for (auto& v : gridRight) {
		for (auto& x : v) { cout << x << " "; }
		cout << endl;
	}
	for (auto& v : gridBot) {
		for (auto& x : v) { cout << x << " "; }
		cout << endl;
	}

	int prevXor = 0;
	while (k--) {
		int x; cin >> x; 
		x ^= prevXor;

		int i = m[x].first, j = m[x].second;
		cout << i + 1 << " " << j + 1 << endl;

		prevXor = x;
	}
}