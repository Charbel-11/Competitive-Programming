#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
using namespace std;
typedef vector<string>(*gridOperation) (const vector<string>&);

vector<string> rotate(const vector<string>& v) {
	int r = (int)v.size(), c = (int)v[0].size();
	vector<string> res(c, string(r, '0'));
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			res[c - 1 - j][i] = v[i][j];
	return res;
}

vector<string> doNothing(const vector<string>& v) { return v; }

vector<string> horizontalFlip(const vector<string>& v) {
	int r = (int)v.size(), c = (int)v[0].size();
	vector<string> res = v;
	for (int i = 0; i < r; i++)
		for (int j = 0, k = c - 1; j < k; j++, k--)
			swap(res[i][j], res[i][k]);
	return res;
}

vector<string> verticalFlip(const vector<string>& v) {
	int r = (int)v.size(), c = (int)v[0].size();
	vector<string> res = v;
	for (int j = 0; j < c; j++)
		for (int i = 0, k = r - 1; i < k; i++, k--)
			swap(res[i][j], res[k][j]);
	return res;
}

gridOperation operations[3] = { doNothing, verticalFlip, horizontalFlip };

int findMatches(const vector<string>& a, const vector<string>& b) {
	int r1 = (int)a.size(), c1 = (int)a[0].size();
	int r2 = (int)b.size(), c2 = (int)b[0].size();

	int res = 0;
	for (int i = 0; i < r2; i++) for (int j = 0; j < c2; j++) { //Top Left of A
		int cur = 0; for (int k = 0; k < r1 && i + k < r2; k++)
			for (int l = 0; l < c1 && j + l < c2; l++)
				cur += (a[k][l] == '#' && b[i + k][j + l] == '#');
		res = max(res, cur);
	}
	return res;
}

int solve(vector<string>& a, vector<string>& b) {
	int res = 0;
	for (int rA = 0; rA < 8; rA++, a = rotate(a))
		for (int rB = 0; rB < 8; rB++, b = rotate(b))
			for (int i = 0; i < 3; i++) {
				a = operations[i](a);
				for (int j = 0; j < 3; j++) {
					b = operations[j](b);
					res = max(res, findMatches(a, b));
					b = operations[j](b);
				}
				a = operations[i](a);
			}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t; cin >> t; while (t--) {
		vector<string> a, b;
		int r1, c1; cin >> r1 >> c1; a.resize(r1);
		for (auto& x : a) { cin >> x; }
		int r2, c2; cin >> r2 >> c2; b.resize(r2);
		for (auto& x : b) { cin >> x; }

		int res1 = solve(a, b);
		int res2 = solve(b, a);
		int res = max(res1, res2);
		cout << res << '\n';
	}
	cin.ignore(2); return 0;
}