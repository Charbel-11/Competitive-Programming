#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#include <assert.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

vector<int> match;

bool isOp(char c) {
	return (c == '-' || c == '+' || c == '*');
}

bool isNum(char c) {
	return (c >= '0' && c <= '9');
}

bool isValid(string& s) {
	int n = s.size();
	for (int i = 0; i < n - 1; i++) {
		if (isOp(s[i]) && isOp(s[i + 1])) { return false; }
		if (s[i] == '(' && s[i + 1] == ')') { return false; }
		if (isOp(s[i]) && s[i + 1] == ')') { return false; }
		if (s[i] == ')' && isNum(s[i + 1])) { return false; }
		if (isNum(s[i]) && s[i + 1] == '(') { return false; }
		if (isOp(s[i + 1]) && s[i] == '(') { return false; }
	}
	if (isOp(s[n - 1]) || isOp(s[0])) { return false; }

	int open = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') { open++; }
		else if (s[i] == ')') { open--; }
		if (open < 0) { return false; }
	}
	if (open > 0) { return false; }

	return true;
}

ll getNextNumber(string& s, int& idx) {
	ll curNum = 0;
	while (idx < s.size() && isNum(s[idx])) {
		curNum *= 10; curNum += (s[idx] - '0');
		curNum %= mod; idx++;
	}
	return curNum;
}

ll evaluate(string& s, int l, int r, int& idx);

ll getNextProducts(string& s, int l, int r, int& idx) {
	int n = s.size();

	ll curNum = 1;
	while (true) {
		ll nextNum = 1;
		if (s[idx] == '(') {
			idx++;
			nextNum = evaluate(s, idx, match[idx - 1] - 1, idx);
			idx++;
		}
		else { nextNum = getNextNumber(s, idx); }

		curNum *= nextNum; curNum %= mod;
		if (idx == r + 1 || s[idx] != '*') { return curNum; }
		idx++;
	}
}

ll evaluate(string& s, int l, int r, int& idx) {
	int n = s.size();
	ll curFactor = 1, prefSum = 0;

	while (true) {
		ll curNum = getNextProducts(s, l, r, idx);

		curNum *= curFactor;
		prefSum += curNum;	prefSum %= mod;
		if (prefSum < 0) { prefSum += mod; }

		if (idx == r + 1) { return prefSum; }
		else if (s[idx] == '+') { idx++; curFactor = 1; }
		else if (s[idx] == '-') { idx++; curFactor = -1; }
	}
}

void findMatches(string& s, int& idx) {
	int cur = -1;
	while (idx < s.size() && s[idx] != '(') { idx++; }
	if (idx == s.size()) { return; }
	cur = idx; idx++;

	while (true) {
		while (s[idx] != '(' && s[idx] != ')') { idx++; }
		if (s[idx] == '(') { findMatches(s, idx); }
		else if (s[idx] == ')') { match[cur] = idx; idx++; return; }
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		string exp; cin >> exp;
		if (!isValid(exp)) { cout << "invalid" << '\n'; continue; }

		match.clear(); match.resize(exp.size());
		int idx = 0;
		while (idx < exp.size()) { findMatches(exp, idx); }

		idx = 0;
		cout << evaluate(exp, 0, exp.size() - 1, idx) << '\n';
	}
}